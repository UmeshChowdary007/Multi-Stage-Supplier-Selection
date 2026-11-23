#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Multi-Stage Supplier Selection using Backward Dynamic Programming.
// Cost values are illustrative units, not actual market prices.

const int STAGES = 4;
const int OPTIONS = 3;

const string stageNames[STAGES] = {
    "Raw Material Supplier", "Manufacturer", "Distributor", "Hospital"
};

const string optionNames[STAGES][OPTIONS] = {
    {"R1", "R2", "R3"},
    {"M1", "M2", "M3"},
    {"D1", "D2", "D3"},
    {"H1", "H2", "H3"}
};

// cost[stage][current option][next-stage option]
const int cost[STAGES - 1][OPTIONS][OPTIONS] = {
    {{4, 8, 6}, {5, 3, 7}, {9, 6, 4}}, // Suppliers -> Manufacturers
    {{5, 7, 4}, {6, 3, 8}, {4, 5, 2}}, // Manufacturers -> Distributors
    {{3, 6, 5}, {4, 2, 7}, {6, 3, 4}}  // Distributors -> Hospitals
};

struct DPResult {
    int minimumCost;
    vector<int> path;
    int dp[STAGES][OPTIONS];
    int nextOption[STAGES][OPTIONS];
};

void displayCostMatrices() {
    cout << "\n========== COST MATRICES ==========\n";
    for (int s = 0; s < STAGES - 1; ++s) {
        cout << "\n" << stageNames[s] << " -> " << stageNames[s + 1] << "\n";
        cout << setw(12) << " ";
        for (int k = 0; k < OPTIONS; ++k)
            cout << setw(8) << optionNames[s + 1][k];
        cout << '\n';

        for (int j = 0; j < OPTIONS; ++j) {
            cout << setw(12) << optionNames[s][j];
            for (int k = 0; k < OPTIONS; ++k)
                cout << setw(8) << cost[s][j][k];
            cout << '\n';
        }
    }
    cout << "\nNote: All costs are illustrative units.\n";
}

DPResult solveUsingDP() {
    DPResult result;
    const int INF = numeric_limits<int>::max() / 4;

    for (int i = 0; i < STAGES; ++i) {
        for (int j = 0; j < OPTIONS; ++j) {
            result.dp[i][j] = INF;
            result.nextOption[i][j] = -1;
        }
    }

    // Base case: no remaining cost after reaching a hospital.
    for (int j = 0; j < OPTIONS; ++j)
        result.dp[STAGES - 1][j] = 0;

    // Backward DP recurrence:
    // DP[i][j] = min_k (cost[i][j][k] + DP[i+1][k])
    for (int i = STAGES - 2; i >= 0; --i) {
        for (int j = 0; j < OPTIONS; ++j) {
            for (int k = 0; k < OPTIONS; ++k) {
                int candidate = cost[i][j][k] + result.dp[i + 1][k];
                if (candidate < result.dp[i][j]) {
                    result.dp[i][j] = candidate;
                    result.nextOption[i][j] = k;
                }
            }
        }
    }

    // Select the best starting supplier.
    int start = 0;
    for (int j = 1; j < OPTIONS; ++j) {
        if (result.dp[0][j] < result.dp[0][start])
            start = j;
    }

    result.minimumCost = result.dp[0][start];

    // Reconstruct the optimal path.
    result.path.resize(STAGES);
    result.path[0] = start;
    for (int i = 0; i < STAGES - 1; ++i)
        result.path[i + 1] = result.nextOption[i][result.path[i]];

    return result;
}

void displayDPTable(const DPResult& result) {
    cout << "\n========== BACKWARD DP TABLE ==========\n";
    for (int i = 0; i < STAGES; ++i) {
        cout << stageNames[i] << ": ";
        for (int j = 0; j < OPTIONS; ++j) {
            cout << optionNames[i][j] << " = " << result.dp[i][j];
            if (j < OPTIONS - 1) cout << " | ";
        }
        cout << '\n';
    }
}

void displayOptimalPath(const DPResult& result) {
    cout << "\n========== OPTIMAL SUPPLY CHAIN ==========\n";
    cout << "Selected path: ";
    for (int i = 0; i < STAGES; ++i) {
        cout << optionNames[i][result.path[i]];
        if (i < STAGES - 1) cout << " -> ";
    }
    cout << "\n\nTransition costs:\n";

    int total = 0;
    for (int i = 0; i < STAGES - 1; ++i) {
        int from = result.path[i];
        int to = result.path[i + 1];
        int edgeCost = cost[i][from][to];
        cout << optionNames[i][from] << " -> "
             << optionNames[i + 1][to] << " = " << edgeCost << '\n';
        total += edgeCost;
    }
    cout << "Total minimum cost = " << total << '\n';
}

struct BruteForceResult {
    int minimumCost;
    long long combinationsChecked;
    vector<int> bestPath;
};

void enumeratePaths(int stage, int currentCost,
                    vector<int>& currentPath, BruteForceResult& result) {
    if (stage == STAGES - 1) {
        ++result.combinationsChecked;
        if (currentCost < result.minimumCost) {
            result.minimumCost = currentCost;
            result.bestPath = currentPath;
        }
        return;
    }

    for (int next = 0; next < OPTIONS; ++next) {
        currentPath.push_back(next);
        enumeratePaths(stage + 1,
                       currentCost + cost[stage][currentPath[stage]][next],
                       currentPath, result);
        currentPath.pop_back();
    }
}

BruteForceResult solveUsingBruteForce() {
    BruteForceResult result;
    result.minimumCost = numeric_limits<int>::max();
    result.combinationsChecked = 0;

    vector<int> currentPath;
    for (int start = 0; start < OPTIONS; ++start) {
        currentPath.push_back(start);
        enumeratePaths(0, 0, currentPath, result);
        currentPath.pop_back();
    }
    return result;
}

void displayBruteForceResult(const BruteForceResult& result) {
    cout << "\n========== BRUTE-FORCE VERIFICATION ==========\n";
    cout << "Complete combinations checked: "
         << result.combinationsChecked << '\n';
    cout << "Best path found: ";
    for (int i = 0; i < STAGES; ++i) {
        cout << optionNames[i][result.bestPath[i]];
        if (i < STAGES - 1) cout << " -> ";
    }
    cout << "\nMinimum cost found by brute force: "
         << result.minimumCost << '\n';
}

void compareResults(const DPResult& dp, const BruteForceResult& brute) {
    cout << "\n========== DP VS BRUTE FORCE ==========\n";
    cout << "Dynamic Programming minimum cost: " << dp.minimumCost << '\n';
    cout << "Brute-Force minimum cost:          " << brute.minimumCost << '\n';

    if (dp.minimumCost == brute.minimumCost)
        cout << "Verification: SUCCESS - Both methods give the same minimum cost.\n";
    else
        cout << "Verification: FAILED - Results do not match.\n";

    cout << "\n========== COMPLEXITY ANALYSIS ==========\n";
    cout << "Let S = number of stages and N = options per stage.\n";
    cout << "Brute-force time complexity: O(N^S)\n";
    cout << "DP time complexity:          O(S * N^2)\n";
    cout << "DP space complexity:         O(S * N)\n";
    cout << "For this example: S = " << STAGES << ", N = " << OPTIONS << '\n';
    cout << "Brute-force combinations: " << OPTIONS << "^" << STAGES
         << " = " << brute.combinationsChecked << '\n';
}

int main() {
    cout << "====================================================\n";
    cout << " MULTI-STAGE SUPPLIER SELECTION USING DYNAMIC PROGRAMMING\n";
    cout << "====================================================\n";

    displayCostMatrices();

    DPResult dpResult = solveUsingDP();
    displayDPTable(dpResult);
    displayOptimalPath(dpResult);

    BruteForceResult bruteResult = solveUsingBruteForce();
    displayBruteForceResult(bruteResult);
    compareResults(dpResult, bruteResult);

    cout << "\nProgram completed successfully.\n";
    return 0;
}
