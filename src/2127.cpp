#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumInvitations(vector<int>& favorite) {
        int retVal = 0;

        int favoriteSize = favorite.size();

        // Calculate in-degree for each node
        vector<int> inDegree(favoriteSize, 0);
        for (int person = 0; person < favoriteSize; ++person) {
            inDegree[favorite[person]]++;
        }

        // Topological sorting to remove non-cycle nodes
        queue<int> TopologicalSortingQueue;
        for (int person = 0; person < favoriteSize; ++person) {
            if (inDegree[person] == 0) {
                TopologicalSortingQueue.push(person);
            }
        }

        vector<int> depth(favoriteSize, 1);  // Depth of each node

        while (TopologicalSortingQueue.empty() == false) {
            int currentNode = TopologicalSortingQueue.front();
            TopologicalSortingQueue.pop();

            int nextNode = favorite[currentNode];
            depth[nextNode] = max(depth[nextNode], depth[currentNode] + 1);

            inDegree[nextNode]--;
            if (inDegree[nextNode] == 0) {
                TopologicalSortingQueue.push(nextNode);
            }
        }

        // Detect cycles
        int longestCycle = 0;
        int twoCycleInvitations = 0;
        for (int person = 0; person < favoriteSize; ++person) {
            if (inDegree[person] == 0) {  // Already processed
                continue;
            }

            int cycleLength = 0;
            int current = person;
            while (inDegree[current] != 0) {
                inDegree[current] = 0;  // Mark as visited
                cycleLength++;
                current = favorite[current];
            }

            if (cycleLength == 2) {  // For 2-cycles, add the depth of both nodes
                twoCycleInvitations += depth[person] + depth[favorite[person]];
            } else {
                longestCycle = max(longestCycle, cycleLength);
            }
        }

        retVal = max(longestCycle, twoCycleInvitations);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> favorite;
    };
    vector<subject> testData{{{2, 2, 1, 2}}, {{1, 2, 0}}, {{3, 0, 1, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: favorite = [2,2,1,2]
     *  Output: 3
     *
     *  Input: favorite = [1,2,0]
     *  Output: 3
     *
     *  Input: favorite = [3,0,1,4,1]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: favorite = [";
        for (long unsigned int j = 0; j < testData[i].favorite.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].favorite[j];
        }
        cout << "]\n";

        answer = cSolution.maximumInvitations(testData[i].favorite);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
