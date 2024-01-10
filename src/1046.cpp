#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int lastStoneWeight(vector<int>& stones) {
        int retVal = 0;

        priority_queue<int> priorityQueue;
        for (int stone : stones) {
            priorityQueue.push(stone);
        }

        while (priorityQueue.size() > 1) {
            int first = priorityQueue.top();
            priorityQueue.pop();
            int second = priorityQueue.top();
            priorityQueue.pop();
            if (first > second) {
                priorityQueue.push(first - second);
            }
        }
        if (priorityQueue.empty() == false) {
            retVal = priorityQueue.top();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> stones;
    };
    vector<subject> testData{{{2, 7, 4, 1, 8, 1}}, {{1}}, {{3, 7, 2}}, {{2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: stones = [2,7,4,1,8,1]
     *  Output: 1
     *
     *  Input: stones = [1]
     *  Output: 1
     *
     *  Input: stones = [3,7,2]
     *  Output: 2
     *
     *  Input: stones = [2,2]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: stones = [";
        for (long unsigned int j = 0; j < testData[i].stones.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].stones[j];
        }
        cout << "]\n";

        answer = cSolution.lastStoneWeight(testData[i].stones);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
