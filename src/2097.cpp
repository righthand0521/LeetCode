#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        vector<vector<int>> retVal;

        // Build the adjacency list and track in-degrees and out-degrees
        unordered_map<int, deque<int>> adjacencyMatrix;
        unordered_map<int, int> inDegree;
        unordered_map<int, int> outDegree;
        for (const auto& pair : pairs) {
            int start = pair[0];
            int end = pair[1];
            adjacencyMatrix[start].push_back(end);
            outDegree[start]++;
            inDegree[end]++;
        }

        // Find the start node (outDegree == inDegree + 1)
        int startNode = -1;
        for (const auto& entry : outDegree) {
            int node = entry.first;
            if (outDegree[node] == inDegree[node] + 1) {
                startNode = node;
                break;
            }
        }
        if (startNode == -1) {  // If no such node exists, start from the first pair's first element
            startNode = pairs[0][0];
        }

        vector<int> result;
        // Iterative DFS using stack
        stack<int> nodeStack;
        nodeStack.push(startNode);
        while (nodeStack.empty() == false) {
            int node = nodeStack.top();
            if (adjacencyMatrix[node].empty() == false) {  // Visit the next node
                int nextNode = adjacencyMatrix[node].front();
                adjacencyMatrix[node].pop_front();
                nodeStack.push(nextNode);
            } else {  // No more neighbors to visit, add node to result
                result.push_back(node);
                nodeStack.pop();
            }
        }
        reverse(result.begin(), result.end());  // Reverse the result since we collected nodes in reverse order

        // Construct the result pairs
        int resultSize = result.size();
        for (int i = 1; i < resultSize; ++i) {
            retVal.push_back({result[i - 1], result[i]});
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> pairs;
    };
    vector<subject> testData{
        {{{5, 1}, {4, 5}, {11, 9}, {9, 4}}}, {{{1, 3}, {3, 2}, {2, 1}}}, {{{1, 2}, {1, 3}, {2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
     *  Output: [[11,9],[9,4],[4,5],[5,1]]
     *
     *  Input: pairs = [[1,3],[3,2],[2,1]]
     *  Output: [[1,3],[3,2],[2,1]]
     *
     *  Input: pairs = [[1,2],[1,3],[2,1]]
     *  Output: [[1,2],[2,1],[1,3]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pairs = [";
        for (long unsigned int j = 0; j < testData[i].pairs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].pairs[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].pairs[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.validArrangement(testData[i].pairs);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
