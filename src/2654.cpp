#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        int numberOfOne = 0;
        int greatestCommonDivisor = 0;
        for (int num : nums) {
            if (num == 1) {
                numberOfOne++;
            }
            greatestCommonDivisor = gcd(greatestCommonDivisor, num);
        }
        if (numberOfOne > 0) {
            retVal = numsSize - numberOfOne;
            return retVal;
        } else if (greatestCommonDivisor > 1) {
            return retVal;
        }

        int minNumsSize = numsSize;
        for (int i = 0; i < numsSize; i++) {
            greatestCommonDivisor = 0;
            for (int j = i; j < numsSize; j++) {
                greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j]);
                if (greatestCommonDivisor == 1) {
                    minNumsSize = min(minNumsSize, j - i + 1);
                    break;
                }
            }
        }
        retVal = minNumsSize + numsSize - 2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 6, 3, 4}}, {{2, 10, 6, 14}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,6,3,4]
     *  Output: 4
     *
     *  Input: nums = [2,10,6,14]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
