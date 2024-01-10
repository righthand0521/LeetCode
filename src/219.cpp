#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            auto iterator = hashTable.find(nums[i]);
            if (iterator != hashTable.end()) {
                if (i - iterator->second <= k) {
                    retVal = true;
                    break;
                }
            }
            hashTable[nums[i]] = i;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 1}, 3}, {{1, 0, 1, 1}, 1}, {{1, 2, 3, 1, 2, 3}, 2}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [1,2,3,1], k = 3
     *  Output: true
     *
     *  Input: nums = [1,0,1,1], k = 1
     *  Output: true
     *
     *  Input: nums = [1,2,3,1,2,3], k = 2
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.containsNearbyDuplicate(testData[i].nums, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
