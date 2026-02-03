#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxSumTrionic(vector<int>& nums) {
        long long retVal = numeric_limits<long long>::min();

        int numsSize = nums.size();

        int p, q, j;
        long long maxSum, currrentSum, res;
        for (int i = 0; i < numsSize; i++) {
            j = i + 1;
            res = 0;

            // first segment
            for (; ((j < numsSize) && (nums[j - 1] < nums[j])); j++);
            p = j - 1;
            if (p == i) {
                continue;
            }

            // second segment
            res += (nums[p] + nums[p - 1]);
            for (; ((j < numsSize) && (nums[j - 1] > nums[j])); j++) {
                res += nums[j];
            }
            q = j - 1;
            if (q == p || q == numsSize - 1 || (nums[j] <= nums[q])) {
                i = q;
                continue;
            }

            // third segment
            res += nums[q + 1];

            // find the maximum sum of the third segment
            maxSum = 0;
            currrentSum = 0;
            for (int k = q + 2; k < numsSize && nums[k] > nums[k - 1]; k++) {
                currrentSum += nums[k];
                maxSum = max(maxSum, currrentSum);
            }
            res += maxSum;

            // find the maximum sum of the first segment
            maxSum = 0;
            currrentSum = 0;
            for (int k = p - 2; k >= i; k--) {
                currrentSum += nums[k];
                maxSum = max(maxSum, currrentSum);
            }
            res += maxSum;

            // update answer
            retVal = max(retVal, res);
            i = q - 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, -2, -1, -3, 0, 2, -1}}, {{1, 4, 2, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,-2,-1,-3,0,2,-1]
     *  Output: -4
     *
     *  Input: nums = [1,4,2,7]
     *  Output: 14
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxSumTrionic(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
