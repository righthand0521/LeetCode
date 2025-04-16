#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countGood(vector<int>& nums, int k) {
        long long retVal = 0;

        unordered_map<int, int> hashTable;

        int numsSize = nums.size();
        int same = 0;
        int right = -1;
        for (int left = 0; left < numsSize; ++left) {
            while ((same < k) && (right + 1 < numsSize)) {
                ++right;
                same += hashTable[nums[right]];
                ++hashTable[nums[right]];
            }

            if (same >= k) {
                retVal += (numsSize - right);
            }

            --hashTable[nums[left]];
            same -= hashTable[nums[left]];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 1, 1, 1, 1}, 10}, {{3, 1, 4, 3, 2, 2, 4}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1,1,1], k = 10
     *  Output: 1
     *
     *  Input: nums = [3,1,4,3,2,2,4], k = 2
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.countGood(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
