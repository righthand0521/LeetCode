#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void dfs(vector<vector<int>>& adjacencyList, vector<bool>& visited, int stone) {
        visited[stone] = true;
        for (int neighbor : adjacencyList[stone]) {
            if (visited[neighbor] == false) {
                dfs(adjacencyList, visited, neighbor);
            }
        }
    }

   public:
    int removeStones(vector<vector<int>>& stones) {
        int retVal = 0;

        int stonesSize = stones.size();

        vector<vector<int>> adjacencyList(stonesSize);
        for (int i = 0; i < stonesSize; i++) {
            for (int j = i + 1; j < stonesSize; j++) {
                if ((stones[i][0] == stones[j][0]) || (stones[i][1] == stones[j][1])) {
                    adjacencyList[i].push_back(j);
                    adjacencyList[j].push_back(i);
                }
            }
        }

        vector<bool> visited(stonesSize, false);
        int numOfConnectedComponents = 0;
        for (int i = 0; i < stonesSize; i++) {
            if (visited[i] == false) {
                dfs(adjacencyList, visited, i);
                numOfConnectedComponents++;
            }
        }

        retVal = stonesSize - numOfConnectedComponents;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> stones;
    };
    vector<subject> testData{
        {{{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}}}, {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}}, {{{0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
     *  Output: 5
     *
     *  Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
     *  Output: 3
     *
     *  Input: stones = [[0,0]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: stones = [";
        for (long unsigned int j = 0; j < testData[i].stones.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].stones[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].stones[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.removeStones(testData[i].stones);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
