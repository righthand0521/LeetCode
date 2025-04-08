#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumOperations(vector<int>& nums) {
        int retVal = 0;

        vector<int> hashTable(128, 0);  // 1 <= nums.length <= 100

        int numsSize = nums.size();
        for (int i = numsSize - 1; i >= 0; --i) {
            if (hashTable[nums[i]] == 1) {
                retVal = i / 3 + 1;
                break;
            }
            hashTable[nums[i]] = 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4, 2, 3, 3, 5, 7}}, {{4, 5, 6, 4, 4}}, {{6, 7, 8, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,2,3,3,5,7]
     *  Output: 2
     *
     *  Input: nums = [4,5,6,4,4]
     *  Output: 2
     *
     *  Input: nums = [6,7,8,9]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
