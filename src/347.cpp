#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            ++hashTable[num];
        }

        priority_queue<pair<int, int>> priorityQueue;
        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            priorityQueue.push(make_pair(iterator->second, iterator->first));
        }
        for (int i = 0; i < k; ++i) {
            retVal.emplace_back(priorityQueue.top().second);
            priorityQueue.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 1, 1, 2, 2, 3}, 2}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1,2,2,3], k = 2
     *  Output: [1,2]
     *
     *  Input: nums = [1], k = 1
     *  Output: [1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.topKFrequent(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
