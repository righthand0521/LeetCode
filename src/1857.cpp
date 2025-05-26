#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    constexpr static int colorsOptions = 26;  // colors consists of lowercase English letters.

   public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int retVal = -1;

        //
        int colorsSize = colors.size();
        vector<vector<int>> adjacent(colorsSize);
        vector<int> indegree(colorsSize);
        for (auto&& edge : edges) {
            ++indegree[edge[1]];
            adjacent[edge[0]].push_back(edge[1]);
        }

        //
        int colorsFound = 0;
        vector<array<int, colorsOptions>> colorsRecord(colorsSize);
        queue<int> colorsQueue;
        for (int i = 0; i < colorsSize; ++i) {
            if (indegree[i] == 0) {
                colorsQueue.push(i);
            }
        }

        while (colorsQueue.empty() == false) {
            int u = colorsQueue.front();
            colorsQueue.pop();
            ++colorsRecord[u][colors[u] - 'a'];
            ++colorsFound;

            for (int v : adjacent[u]) {
                --indegree[v];

                for (int c = 0; c < colorsOptions; ++c) {
                    colorsRecord[v][c] = max(colorsRecord[v][c], colorsRecord[u][c]);
                }

                if (indegree[v] == 0) {
                    colorsQueue.push(v);
                }
            }
        }

        //
        if (colorsFound != colorsSize) {
            return retVal;
        }

        retVal = 0;
        for (int i = 0; i < colorsSize; ++i) {
            retVal = max(retVal, *max_element(colorsRecord[i].begin(), colorsRecord[i].end()));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string colors;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{"abaca", {{0, 1}, {0, 2}, {2, 3}, {3, 4}}}, {"a", {{0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
     *  Output: 3
     *
     *  Input: colors = "a", edges = [[0,0]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: colors = \"" << testData[i].colors << "\", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.largestPathValue(testData[i].colors, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
