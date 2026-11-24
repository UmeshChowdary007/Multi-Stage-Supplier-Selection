# Multi-Stage Supplier Selection Using Dynamic Programming

## 📌 Project Overview

The **Multi-Stage Supplier Selection System** is a Design and Analysis of Algorithms (DAA) project that finds the minimum-cost path through a multi-stage supply chain.

The project uses **Dynamic Programming** to identify the most cost-effective combination of suppliers, manufacturers, distributors, and hospitals.

It also implements the **Brute Force approach** to compare the results and efficiency of both algorithms.

## 🎯 Problem Statement

In a medicine supply chain, selecting the best combination of suppliers, manufacturers, distributors, and hospitals is important to minimize the overall cost.

Each transition between two consecutive stages has an associated cost, including purchasing, transportation, and risk.

The objective is to select exactly one option from each stage while minimizing the total cost.

## 🏗️ Project Structure

The supply chain consists of four stages:

1. **Raw Material Suppliers:** R1, R2, R3
2. **Manufacturers:** M1, M2, M3
3. **Distributors:** D1, D2, D3
4. **Hospitals:** H1, H2, H3

Each stage contains three possible options.

## ⚙️ Technologies Used

- C++ – Backend algorithm implementation
- HTML – Website structure
- CSS – Website styling
- JavaScript – Frontend interaction with the backend
- C++ HTTP Library (cpp-httplib) – Communication between the website and C++ backend

## 🧠 Algorithms Implemented

### 1. Dynamic Programming

Dynamic Programming solves the problem by breaking it into smaller subproblems and storing previously calculated results.

**Approach:**
- Start from the final stage.
- Calculate the minimum remaining cost for each option.
- Store the minimum costs in a DP table.
- Store the next selected option to reconstruct the optimal path.
- Identify the minimum-cost route from the first stage to the final stage.

**Time Complexity:** O(S × N²)

**Space Complexity:** O(S × N)

Where:
- S = Number of stages
- N = Number of options in each stage

### 2. Brute Force

The Brute Force approach explores every possible combination of options across all stages and calculates the total cost of each path.

It then selects the path with the minimum total cost.

**Time Complexity:** O(N^S)

**Auxiliary Space Complexity:** O(S)

Where:
- S = Number of stages
- N = Number of options in each stage

## 📊 Sample Cost Matrices

The following illustrative cost matrices represent the transition costs between consecutive stages.

### Suppliers to Manufacturers

| | M1 | M2 | M3 |
|---|---:|---:|---:|
| R1 | 4 | 8 | 6 |
| R2 | 5 | 3 | 7 |
| R3 | 9 | 6 | 4 |

### Manufacturers to Distributors

| | D1 | D2 | D3 |
|---|---:|---:|---:|
| M1 | 5 | 7 | 4 |
| M2 | 6 | 3 | 8 |
| M3 | 4 | 5 | 2 |

### Distributors to Hospitals

| | H1 | H2 | H3 |
|---|---:|---:|---:|
| D1 | 3 | 6 | 5 |
| D2 | 4 | 2 | 7 |
| D3 | 6 | 3 | 4 |

*Note: These values are illustrative cost units used for demonstrating the algorithms, not actual market prices.*

## 💻 Expected Result

Both algorithms identify the same optimal path.

**Optimal Path:**

`R2 → M2 → D2 → H2`

**Minimum Total Cost: 8**

### Algorithm Comparison

| Parameter | Dynamic Programming | Brute Force |
|---|---|---|
| Approach | Stores and reuses results | Explores all combinations |
| Time Complexity | O(S × N²) | O(N^S) |
| Paths Considered | Avoids repeated calculations | 81 combinations |
| Optimal Result | 8 | 8 |

## 🌐 Website Features

- Interactive website interface
- Displays the problem statement and supply chain stages
- Displays transition cost matrices
- Executes the Dynamic Programming algorithm
- Executes the Brute Force algorithm
- Displays the optimal path and minimum total cost
- Allows comparison of both algorithms

## 📁 Project Files

```text
Multi-Stage-Supplier-Selection/
│
├── index.html       # Website structure
├── style.css        # Website styling
├── script.js        # Frontend functionality
├── server.cpp       # C++ backend and algorithms
├── httplib.h        # HTTP server library
└── README.md        # Project documentation
```

## 🚀 How to Run the Project

### Prerequisites

- Windows operating system
- Visual Studio Code or any C++ editor
- GCC/G++ compiler with C++17 support
- Internet connection to download the HTTP library

### Step 1: Download the Project

Clone the repository:

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

Alternatively, download the repository as a ZIP file and extract it.

### Step 2: Download the HTTP Library

Download `httplib.h` from:

https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

Place the downloaded file in the project folder.

### Step 3: Compile the C++ Backend

Open the project folder in the terminal and execute:

```bash
g++ -std=c++17 server.cpp -o server.exe -lws2_32
```

### Step 4: Run the Server

```bash
.\server.exe
```

### Step 5: Open the Website

Open your browser and visit:

```text
http://localhost:8080
```

The website is now ready to use.

## 📌 Conclusion

This project demonstrates how Dynamic Programming can efficiently solve a multi-stage supplier selection problem by avoiding repeated calculations.

The Brute Force approach explores all possible combinations, while Dynamic Programming reduces unnecessary computation by storing and reusing intermediate results.

Both approaches produce the same optimal solution, demonstrating the effectiveness of Dynamic Programming for multi-stage optimization problems.

---

## 👥 Project Information

**Subject:** Design and Analysis of Algorithms (DAA)

**Project Title:** Multi-Stage Supplier Selection Using Dynamic Programming

**Implementation Language:** C++

**Project Type:** Algorithm Implementation with Web Interface
