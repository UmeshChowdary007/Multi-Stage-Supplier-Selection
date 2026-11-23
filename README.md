# Multi-Stage Supplier Selection Using Dynamic Programming

## Project Overview
This project focuses on selecting the most cost-effective path in a multi-stage medicine supply chain using Dynamic Programming.

The supply chain consists of four stages:

1. Raw Material Supplier
2. Manufacturer
3. Distributor
4. Hospital

The objective is to select exactly one option from each stage while minimizing the total cost.

## Algorithm Used
**Dynamic Programming (DP)**

The problem is modeled as a multistage directed weighted graph. A backward Dynamic Programming approach is used to calculate the minimum remaining cost at each stage and reconstruct the optimal path.

## Technologies Used
- Programming Language: C++
- Algorithm: Dynamic Programming
- Compiler: GCC (C++17)

## Project Files
- `multistage_supplier_selection.cpp` – Complete C++ source code.
- `DESIGN-AND-ANALYSIS-OF-ALGORITHMS.pptx` – Project presentation.

## How to Compile and Run

Compile the program:

```bash
g++ -std=c++17 multistage_supplier_selection.cpp -o supplier
```

Run on Windows:

```bash
.\supplier.exe
```

Run on Linux:

```bash
./supplier
```

## Expected Result
- Optimal path: R2 → M2 → D2 → H2
- Minimum total cost: 8
- Brute-force combinations checked: 81

The Dynamic Programming solution and brute-force solution produce the same optimal result.

## Time and Space Complexity

| Approach | Time Complexity | Space Complexity |
|---|---|---|
| Brute Force | O(N^S) | O(S) auxiliary space |
| Dynamic Programming | O(S × N²) | O(S × N) |

Where:
- N = Number of options per stage
- S = Number of stages

## Conclusion
This project demonstrates how Dynamic Programming efficiently solves a multistage supplier selection problem by finding the minimum-cost path and avoiding repeated calculations.
