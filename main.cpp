#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student { int id; string name; };

struct SearchResult { bool found = false; int comparisons = 0; };

struct BSTNode {
    Student data;
    BSTNode *left = nullptr, *right = nullptr;
    explicit BSTNode(Student s) : data(std::move(s)) {}
};

class BST {
    BSTNode* root = nullptr;
    static BSTNode* insertNode(BSTNode* node, const Student& s) {
        if (!node) return new BSTNode(s);
        if (s.id < node->data.id) node->left = insertNode(node->left, s);
        else if (s.id > node->data.id) node->right = insertNode(node->right, s);
        return node;
    }
    static void inorderNode(BSTNode* node) {
        if (!node) return;
        inorderNode(node->left); cout << node->data.id << " "; inorderNode(node->right);
    }
    static int heightNode(BSTNode* node) {
        if (!node) return 0;
        return 1 + max(heightNode(node->left), heightNode(node->right));
    }
    static void destroy(BSTNode* node) {
        if (!node) return;
        destroy(node->left); destroy(node->right); delete node;
    }
public:
    ~BST() { destroy(root); }
    void insert(const Student& s) { root = insertNode(root, s); }
    SearchResult search(int key) const {
        SearchResult r; BSTNode* cur = root;
        while (cur) {
            ++r.comparisons;
            if (key == cur->data.id) { r.found = true; break; }
            cur = key < cur->data.id ? cur->left : cur->right;
        }
        return r;
    }
    int height() const { return heightNode(root); }
    void inorder() const { inorderNode(root); cout << "\n"; }
};

struct AVLNode {
    Student data;
    AVLNode *left = nullptr, *right = nullptr;
    int h = 1;
    explicit AVLNode(Student s) : data(std::move(s)) {}
};

class AVL {
    AVLNode* root = nullptr;
    static int h(AVLNode* n) { return n ? n->h : 0; }
    static int balance(AVLNode* n) { return n ? h(n->left) - h(n->right) : 0; }
    static void update(AVLNode* n) { n->h = 1 + max(h(n->left), h(n->right)); }
    static AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left; AVLNode* t = x->right;
        x->right = y; y->left = t; update(y); update(x); return x;
    }
    static AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right; AVLNode* t = y->left;
        y->left = x; x->right = t; update(x); update(y); return y;
    }
    static AVLNode* insertNode(AVLNode* n, const Student& s) {
        if (!n) return new AVLNode(s);
        if (s.id < n->data.id) n->left = insertNode(n->left, s);
        else if (s.id > n->data.id) n->right = insertNode(n->right, s);
        else return n;
        update(n); int b = balance(n);
        if (b > 1 && s.id < n->left->data.id) return rotateRight(n);       // LL
        if (b < -1 && s.id > n->right->data.id) return rotateLeft(n);      // RR
        if (b > 1 && s.id > n->left->data.id) { n->left = rotateLeft(n->left); return rotateRight(n); } // LR
        if (b < -1 && s.id < n->right->data.id) { n->right = rotateRight(n->right); return rotateLeft(n); } // RL
        return n;
    }
    static void inorderNode(AVLNode* n) {
        if (!n) return;
        inorderNode(n->left); cout << n->data.id << " "; inorderNode(n->right);
    }
    static void destroy(AVLNode* n) {
        if (!n) return;
        destroy(n->left); destroy(n->right); delete n;
    }
public:
    ~AVL() { destroy(root); }
    void insert(const Student& s) { root = insertNode(root, s); }
    SearchResult search(int key) const {
        SearchResult r; AVLNode* cur = root;
        while (cur) {
            ++r.comparisons;
            if (key == cur->data.id) { r.found = true; break; }
            cur = key < cur->data.id ? cur->left : cur->right;
        }
        return r;
    }
    int height() const { return h(root); }
    void inorder() const { inorderNode(root); cout << "\n"; }
};

class HashTable {
    struct Slot { bool occupied = false; Student data{}; };
    vector<Slot> table;
    int collisions = 0;
    int hashFunction(int key) const { return key % static_cast<int>(table.size()); }
public:
    explicit HashTable(int capacity) : table(capacity) {}
    bool insert(const Student& s) {
        int index = hashFunction(s.id);
        for (int probe = 0; probe < static_cast<int>(table.size()); ++probe) {
            int pos = (index + probe) % static_cast<int>(table.size());
            if (!table[pos].occupied) {
                table[pos].occupied = true; table[pos].data = s; return true;
            }
            if (table[pos].data.id == s.id) return false;
            ++collisions;
        }
        return false;
    }
    SearchResult search(int key) const {
        SearchResult r; int index = hashFunction(key);
        for (int probe = 0; probe < static_cast<int>(table.size()); ++probe) {
            int pos = (index + probe) % static_cast<int>(table.size());
            if (!table[pos].occupied) return r;
            ++r.comparisons;
            if (table[pos].data.id == key) { r.found = true; return r; }
        }
        return r;
    }
    int collisionCount() const { return collisions; }
};

vector<Student> loadData(const string& path) {
    ifstream in(path);
    if (!in) throw runtime_error("Cannot open dataset: " + path);
    string line; getline(in, line); vector<Student> students;
    while (getline(in, line)) {
        stringstream ss(line); string id, name;
        if (getline(ss, id, ',') && getline(ss, name))
            students.push_back({stoi(id), name});
    }
    return students;
}

void printResult(const string& label, const SearchResult& r) {
    cout << left << setw(24) << label << " found=" << (r.found ? "YES" : "NO")
         << ", comparisons/probes=" << r.comparisons << "\n";
}

int main(int argc, char* argv[]) {
    string path = argc > 1 ? argv[1] : "data/students.csv";
    try {
        vector<Student> students = loadData(path);
        BST bst; AVL avl; HashTable hash(67);
        for (const auto& s : students) { bst.insert(s); avl.insert(s); hash.insert(s); }

        const int successfulKey = students.at(0).id;
        const int unsuccessfulKey = 9999;
        cout << "ALGORITHM BATTLE: STUDENT RECORD SEARCH\n";
        cout << "Dataset records: " << students.size() << "\n";
        cout << "Hash table capacity: 67; hash function: key % 67; collision handling: linear probing\n\n";

        cout << "TREE TRAVERSAL (INORDER - BST): "; bst.inorder();
        cout << "TREE TRAVERSAL (INORDER - AVL): "; avl.inorder();
        cout << "\nTREE HEIGHTS (levels):\nBST: " << bst.height() << "\nAVL: " << avl.height() << "\n\n";

        cout << "SUCCESSFUL SEARCH (ID " << successfulKey << ")\n";
        printResult("BST", bst.search(successfulKey));
        printResult("AVL", avl.search(successfulKey));
        printResult("Hashing", hash.search(successfulKey));

        cout << "\nUNSUCCESSFUL SEARCH (ID " << unsuccessfulKey << ")\n";
        printResult("BST", bst.search(unsuccessfulKey));
        printResult("AVL", avl.search(unsuccessfulKey));
        printResult("Hashing", hash.search(unsuccessfulKey));

        cout << "\nINSERTION OBSERVATION:\n";
        cout << "BST: inserted " << students.size() << " records; no balancing is performed.\n";
        cout << "AVL: inserted " << students.size() << " records; rotations maintain balance.\n";
        cout << "Hashing: inserted " << students.size() << " records; collisions during insertion = "
             << hash.collisionCount() << ".\n";
        cout << "\nNOTE: Search comparisons are measured by this program for the stated keys.\n";
        cout << "For hashing, comparisons/probes counts occupied slots checked; collisions counts\n";
        cout << "occupied-slot conflicts encountered during insertion.\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n"; return 1;
    }
    return 0;
}
