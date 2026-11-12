# Algorithm Battle – Technical Assignment Report

## Part A – Problem Selection
**Application:** Student Record Search.

**Problem:** A college must store student records and retrieve a record quickly using a unique student ID. Searching a long list sequentially can require checking many records.

**Need for efficient searching:** Faculty or administrative users may need to retrieve a student's record frequently. A suitable structure should reduce the number of records/slots inspected.

**Reason for comparing the structures:** BST and AVL store keys in ordered tree form and support inorder traversal. Hashing maps a key to a table index and supports fast exact-key lookup. Their behaviour can be compared using the same dataset.

## Part B – Implementation
The program in `src/main.cpp` implements:
1. BST insertion, search and inorder traversal.
2. AVL insertion with LL, RR, LR and RL rotations, search and inorder traversal.
3. Hash table insertion and search using `key % 67`, with linear probing for collisions.

The dataset is `data/students.csv` and contains 40 unique student IDs. All three structures receive the same records in the same order.

## Part C – Mini Experiment
The program performs:
- Successful search for the first student ID in the dataset.
- Unsuccessful search for ID `9999`.
- Insertion of all 40 records.
- Measurement of search comparisons/probes, BST and AVL height, and hash insertion collisions.

**Actual program output:** See `results/experiment_results.txt`. Re-run the program to reproduce the measurements.

## Part D – Algorithm Battle

| Parameter | BST | AVL | Hashing |
|---|---|---|---|
| Search comparisons | Number of visited nodes; depends on shape and key | Number of visited nodes; height remains balanced | Number of occupied slots inspected |
| Insertion | Simple; can become skewed | May perform rotations to maintain balance | Computes an index; linear probes resolve collisions |
| Height | Can grow to O(n) | O(log n) | Not applicable |
| Collisions | Not applicable | Not applicable | Possible; handled by linear probing |
| Ordered traversal | Inorder traversal gives sorted IDs | Inorder traversal gives sorted IDs | Not naturally sorted |

## Part E – Final Verdict
**Recommendation for this application:** Hashing with linear probing is the recommended choice when the main requirement is exact lookup by student ID. It generally provides expected O(1) search when the table has a suitable capacity and load factor.

**Qualification:** AVL is a strong alternative when sorted traversal and predictable O(log n) search are both important. A plain BST is simplest to implement, but its performance can degrade to O(n) if insertion order creates a skewed tree.

The recommendation must be discussed alongside the measurements in `results/experiment_results.txt`. These measurements describe only this dataset, insertion order, search keys, hash function and table capacity; they are not universal performance guarantees.

## Conclusion
The experiment demonstrates that the best structure depends on the application's operations. Hashing is preferred for exact student-ID lookup, while AVL is preferable when ordered operations are also required.
