#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        vector<int> retVal;

        if (k == 1) {
            retVal = nums;
            return retVal;
        }

        int numsSize = nums.size();
        retVal.resize(numsSize - k + 1, -1);
        int consecutiveCount = 1;
        for (int i = 0; i < numsSize - 1; ++i) {
            if (nums[i] + 1 == nums[i + 1]) {
                consecutiveCount++;
            } else {
                consecutiveCount = 1;
            }

            if (consecutiveCount >= k) {
                retVal[i - k + 2] = nums[i + 1];
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
    vector<subject> testData{{{1, 2, 3, 4, 3, 2, 5}, 3}, {{2, 2, 2, 2, 2}, 4}, {{3, 2, 3, 2, 3, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,3,2,5], k = 3
     *  Output: [3,4,-1,-1,-1]
     *
     *  Input: nums = [2,2,2,2,2], k = 4
     *  Output: [-1,-1]
     *
     *  Input: nums = [3,2,3,2,3,2], k = 2
     *  Output: [-1,3,-1,3,-1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.resultsArray(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
