# Algorithm Battle: Student Record Search

## Application
A student record search system stores student ID and name. The student ID is the unique key.

## Implementations
- **Binary Search Tree (BST):** inserts records by key and supports inorder traversal.
- **AVL Tree:** self-balancing BST. It uses LL, RR, LR and RL rotations after insertion.
- **Hashing:** uses `key % 67` and resolves collisions with **linear probing**.

## Dataset
`data/students.csv` contains 40 unique student records. The exact same records and insertion order are used in all three implementations.

## Requirements
- C++ compiler supporting C++11 or later (g++ recommended).
- No external libraries are required.

## Compile and run
From the repository root:

```bash
g++ -std=c++17 -O2 -Wall -Wextra src/main.cpp -o algorithm_battle
./algorithm_battle data/students.csv
```

On Windows PowerShell with MinGW g++:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra src/main.cpp -o algorithm_battle.exe
.lgorithm_battle.exe data/students.csv
```

The program prints tree traversals, heights, successful and unsuccessful search measurements, and insertion/collision observations.

## Experiment method
1. Load the same 40 CSV records in their listed order.
2. Insert every record into BST, AVL and hash table.
3. Search for the first dataset ID (successful search).
4. Search for ID `9999` (unsuccessful search; it is not in the dataset).
5. Record the comparison/probe counts and structural measurements printed by the program.

## Important interpretation
- BST and AVL search comparisons count visited tree nodes.
- Hash search comparisons/probes count occupied slots inspected before finding the key or reaching an empty slot.
- Hash collisions are counted during insertion whenever an occupied slot blocks the initial/current probe position.
- Tree height is reported in levels; an empty tree would have height 0 and a one-node tree height 1.
- Results depend on insertion order, chosen search keys, hash capacity and hash function. Do not claim these results apply to every dataset.

## Viva preparation
Be ready to explain:
- Why student ID is used as a unique search key.
- Why an ordinary BST can become skewed.
- How AVL rotations maintain balance.
- How linear probing checks the next slot after a collision.
- Why hashing is suitable for exact-key lookup, while trees also support sorted traversal and range queries.

## Complexity summary
| Structure | Average search | Worst-case search | Extra observation |
|---|---:|---:|---|
| BST | O(log n) when reasonably balanced | O(n) | Inorder traversal gives sorted IDs |
| AVL | O(log n) | O(log n) | Maintains logarithmic height |
| Hashing (linear probing) | Expected O(1) at a suitable load factor | O(n) | No sorted traversal; performance depends on collisions/load factor |

## Submission
Upload the repository folder (or its ZIP) to GitHub. Submit the GitHub repository URL in Google Classroom along with the assignment report if your faculty requires a separate report.
