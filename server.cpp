
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
#include "httplib.h"

using namespace std;
using namespace httplib;

const int STAGES = 4;
const int OPTIONS = 3;

string stageNames[STAGES] = {
    "Raw Material Supplier",
    "Manufacturer",
    "Distributor",
    "Hospital"
};

string optionNames[STAGES][OPTIONS] = {
    {"R1", "R2", "R3"},
    {"M1", "M2", "M3"},
    {"D1", "D2", "D3"},
    {"H1", "H2", "H3"}
};

int cost[STAGES - 1][OPTIONS][OPTIONS] = {
    {
        {4, 8, 6},
        {5, 3, 7},
        {9, 6, 4}
    },
    {
        {5, 7, 4},
        {6, 3, 8},
        {4, 5, 2}
    },
    {
        {3, 6, 5},
        {4, 2, 7},
        {6, 3, 4}
    }
};

struct DPResult {
    int minimumCost;
    vector<int> path;
    int dp[STAGES][OPTIONS];
    int nextOption[STAGES][OPTIONS];
};

DPResult solveUsingDP() {
    DPResult result;

    for (int i = 0; i < STAGES; i++) {
        for (int j = 0; j < OPTIONS; j++) {
            result.dp[i][j] = 0;
            result.nextOption[i][j] = -1;
        }
    }

    // Base case: final-stage costs are zero
    for (int j = 0; j < OPTIONS; j++) {
        result.dp[STAGES - 1][j] = 0;
    }

    // Backward Dynamic Programming
    for (int i = STAGES - 2; i >= 0; i--) {
        for (int j = 0; j < OPTIONS; j++) {
            int minimum = INT_MAX;

            for (int k = 0; k < OPTIONS; k++) {
                int current = cost[i][j][k]
                            + result.dp[i + 1][k];

                if (current < minimum) {
                    minimum = current;
                    result.nextOption[i][j] = k;
                }
            }

            result.dp[i][j] = minimum;
        }
    }

    // Find the best starting supplier
    int start = 0;

    for (int j = 1; j < OPTIONS; j++) {
        if (result.dp[0][j] < result.dp[0][start]) {
            start = j;
        }
    }

    result.minimumCost = result.dp[0][start];

    // Reconstruct optimal path
    result.path.resize(STAGES);
    result.path[0] = start;

    for (int i = 0; i < STAGES - 1; i++) {
        result.path[i + 1] =
            result.nextOption[i][result.path[i]];
    }

    return result;
}

// Brute Force implementation
struct BruteForceResult {
    int minimumCost = INT_MAX;
    int combinationsChecked = 0;
    vector<int> bestPath;
};

void enumeratePaths(
    int stage,
    int currentOption,
    int totalCost,
    vector<int>& path,
    BruteForceResult& result
) {
    if (stage == STAGES - 1) {
        result.combinationsChecked++;

        if (totalCost < result.minimumCost) {
            result.minimumCost = totalCost;
            result.bestPath = path;
        }

        return;
    }

    for (int next = 0; next < OPTIONS; next++) {
        path.push_back(next);

        enumeratePaths(
            stage + 1,
            next,
            totalCost + cost[stage][currentOption][next],
            path,
            result
        );

        path.pop_back();
    }
}

BruteForceResult solveUsingBruteForce() {
    BruteForceResult result;

    for (int start = 0; start < OPTIONS; start++) {
        vector<int> path;
        path.push_back(start);

        enumeratePaths(0, start, 0, path, result);
    }

    return result;
}

// Convert path to JSON
string pathToJSON(const vector<int>& path) {
    stringstream out;
    out << "[";

    for (int i = 0; i < STAGES; i++) {
        if (i > 0) out << ",";
        out << "\"" << optionNames[i][path[i]] << "\"";
    }

    out << "]";
    return out.str();
}

int main() {
    Server server;

    // Dynamic Programming API
    server.Get("/api/dp", [](const Request&, Response& res) {
        DPResult result = solveUsingDP();

        stringstream out;

        out << "{\"minimumCost\":" << result.minimumCost;
        out << ",\"path\":" << pathToJSON(result.path);
        out << ",\"table\":[";

        for (int i = 0; i < STAGES; i++) {
            if (i > 0) out << ",";
            out << "[";

            for (int j = 0; j < OPTIONS; j++) {
                if (j > 0) out << ",";
                out << result.dp[i][j];
            }

            out << "]";
        }

        out << "]}";

        res.set_content(out.str(), "application/json");
    });

    // Brute Force API
    server.Get("/api/brute", [](const Request&, Response& res) {
        BruteForceResult result = solveUsingBruteForce();

        stringstream out;

        out << "{\"minimumCost\":" << result.minimumCost;
        out << ",\"combinations\":"
            << result.combinationsChecked;
        out << ",\"path\":" << pathToJSON(result.bestPath);
        out << "}";

        res.set_content(out.str(), "application/json");
    });

    // Serve website files
    server.set_mount_point("/", ".");

    cout << "\n========================================\n";
    cout << " MULTI-STAGE SUPPLIER SELECTION\n";
    cout << "========================================\n";
    cout << "Website: http://localhost:8080\n";
    cout << "Press Ctrl+C to stop the server.\n\n";

    server.listen("127.0.0.1", 8080);

    return 0;
}
