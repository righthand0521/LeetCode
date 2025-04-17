#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countPairs(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 1; ++i) {
            for (int j = i + 1; j < numsSize; ++j) {
                if ((nums[i] == nums[j]) && ((i * j) % k == 0)) {
                    retVal++;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{3, 1, 2, 2, 2, 1, 3}, 2}, {{1, 2, 3, 4}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1,2,2,2,1,3], k = 2
     *  Output: 4
     *
     *  Input: nums = [1,2,3,4], k = 1
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.countPairs(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
