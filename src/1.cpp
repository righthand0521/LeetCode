#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            auto iterator = hashTable.find(target - nums[i]);
            if (iterator != hashTable.end()) {
                retVal.push_back(iterator->second);
                retVal.push_back(i);
                return retVal;
            }
            hashTable[nums[i]] = i;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{2, 7, 11, 15}, 9}, {{3, 2, 4}, 6}, {{3, 3}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,7,11,15], target = 9
     *  Output: [0,1]
     *
     *  Input: nums = [3,2,4], target = 6
     *  Output: [1,2]
     *
     *  Input: nums = [3,3], target = 6
     *  Output: [0,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.twoSum(testData[i].nums, testData[i].target);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
