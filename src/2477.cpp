#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long dfs(int node, int parent, vector<vector<int>>& adjacent, int seats, long long& fuel) {
        long long retVal = 1;

        for (int neighbor : adjacent[node]) {
            if (neighbor != parent) {
                retVal += dfs(neighbor, node, adjacent, seats, fuel);
            }
        }

        if (node != 0) {
            // Count the fuel it takes to move to the parent node. Root node does not have any parent so we ignore it.
            fuel += ceil((double)retVal / seats);
        }

        return retVal;
    }
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        long long retVal = 0;

        vector<vector<int>> adjacent(roads.size() + 1);
        for (auto& road : roads) {
            adjacent[road[0]].push_back(road[1]);
            adjacent[road[1]].push_back(road[0]);
        }
        dfs(0, -1, adjacent, seats, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> roads;
        int seats;
    };
    vector<subject> testData{
        {{{0, 1}, {0, 2}, {0, 3}}, 5}, {{{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}}, 2}, {{}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: roads = [[0,1],[0,2],[0,3]], seats = 5
     *  Output: 3
     *
     *  Input: roads = [[3,1],[3,2],[1,0],[0,4],[0,5],[4,6]], seats = 2
     *  Output: 7
     *
     *  Input: roads = [], seats = 1
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: roads = [";
        for (long unsigned int j = 0; j < testData[i].roads.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].roads[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].roads[j][k];
            }
            cout << "]";
        }
        cout << "], seats = " << testData[i].seats << "\n";

        answer = cSolution.minimumFuelCost(testData[i].roads, testData[i].seats);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
