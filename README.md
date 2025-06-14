# Parallel-Minimum-Spanning-Tree
# 🌐 Parallel vs Sequential Minimum Spanning Tree using OpenMP in C

> **Parallel Computing Mini Project**  
> M.Tech – Computer Science  
> University of Hyderabad  
> Author: Vela Poojitha

---

## 📘 Project Overview

This project demonstrates the power of **parallel computing** using OpenMP by implementing and comparing **sequential** and **parallel** versions of the **Minimum Spanning Tree (MST)** algorithm on large graphs.

By applying parallel programming concepts, we aim to reduce the computation time for MST calculation significantly, making it more efficient for large-scale graphs.

---

## 🎯 Objectives

- To implement MST using a standard sequential algorithm.
- To parallelize the MST computation using OpenMP.
- To generate large synthetic graphs for performance testing.
- To analyze and compare execution time between both approaches.

---

## 🧠 Key Concepts Used

- **Graph Theory**: MST (Minimum Spanning Tree)
- **Algorithms**: Likely based on Prim's Algorithm (with modifications)
- **Parallel Computing**: Using OpenMP constructs like `#pragma omp parallel for`
- **Performance Evaluation**: Execution time and speedup analysis

---

## 🛠️ Technologies Used

| Component      | Details                    |
|----------------|-----------------------------|
| Language       | C                           |
| Parallelism    | OpenMP                      |
| Plotting       | Python + Matplotlib (optional) |
| Compiler       | GCC                         |
| OS             | Linux/Windows (tested)      |
| IDE            | VS Code                     |

---

## 🔍 Input Format

Each input graph is a text file with lines like:
node1 node2 weight

For example:
0 1 10
1 2 20
0 2 5


These represent an **undirected weighted graph**.

---

## ⚙️ Compilation

### 🔧 Using Makefile 
To compile the programs at once, use the following command:
```bash
make
```
---

🖥 Manually

or if you want to compile each file manually use the below commands
```bash
gcc -fopenmp parallel_mst.c -o parallel_mst
gcc sequential_mst.c -o sequential_mst
gcc pmst_generatelarge_inputs.c -o generator
```
---

🧪 Running the Programs

1. Generate Input Graph
```bash
./generator 500 > input_500nodes.txt
./generator 1000 > input_1000nodes.txt
```
---

2. Run Sequential MST
   
```bash
./sequential_mst input_500nodes.txt
```
---

3. Run Parallel MST
   
 ```bash
./parallel_mst input_500nodes.txt
```
---

4. Compare Outputs

📊 Sample Output

Sequential MST:
Cost = 78904
Time Taken = 2.68 seconds

Parallel MST (4 threads):
Cost = 78904
Time Taken = 0.92 seconds

---
🧠 Learnings and Observations

Parallelism is highly effective in MST when graphs are large.

OpenMP makes parallelism accessible even in C.

Thread safety and synchronization were carefully handled.

Input generation for large graphs was optimized using randomness.

---

