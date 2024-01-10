#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minJumps(vector<int>& arr) {
        int retVal = 0;

        int len = arr.size();

        /* Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
         *  100: 0, 4
         *  -23: 1, 2
         *  404: 3, 9
         *   23: 5, 6, 7
         *    3: 8
         *
         *  (100) -> (-23) -> (-23) -> (404) -> (100) -> (23) -> (23) -> (23) -> (3) -> (404)
         *    |                          |        ^        |               ^              ^
         *    |                          |        |        +---------------+              |
         *    |                          +--------|---------------------------------------+
         *    +-----------------------------------+
         */
        unordered_map<int, vector<int>> adjacent;
        for (int i = 0; i < len; ++i) {
            adjacent[arr[i]].push_back(i);
        }

        // Breadth-First Search
        queue<int> bfsQueue;
        bfsQueue.push(0);

        vector<bool> visit(len);
        visit[0] = true;

        // https://leetcode.com/problems/jump-game-iv/solutions/502699/java-c-bfs-solution-clean-code-o-n/
        while (bfsQueue.empty() == false) {
            for (int size = bfsQueue.size(); size > 0; --size) {
                int i = bfsQueue.front();
                bfsQueue.pop();

                // Reached to last index
                if (i == len - 1) {
                    return retVal;
                }

                vector<int>& next = adjacent[arr[i]];
                next.push_back(i - 1);
                next.push_back(i + 1);
                for (int j : next) {
                    if ((j >= 0) && (j < len) && (visit[j] == false)) {
                        visit[j] = true;
                        bfsQueue.push(j);
                    }
                }
                next.clear();  // avoid later lookup adjacent arr[i]
            }

            ++retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{100, -23, -23, 404, 100, 23, 23, 23, 3, 404}}, {{7}}, {{7, 6, 9, 6, 9, 6, 9, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
     *  Output: 3
     *
     *  Input: arr = [7]
     *  Output: 0
     *
     *  Input: arr = [7,6,9,6,9,6,9,7]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.minJumps(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
