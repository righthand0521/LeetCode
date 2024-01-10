#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define BINARY_SEARCH (1)
#define AVERAGE (1)
   public:
    int minimizeArrayValue(vector<int>& nums) {
        int retVal = 0;

#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int left = 0;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            bool operationFlag = true;
            /* use long to avoid signed integer overflow
             *  n == nums.length
             *  2 <= n <= 10^5
             *  0 <= nums[i] <= 10^9
             */
            long operation = 0;
            for (auto num : nums) {
                if (num <= middle) {
                    operation += (middle - num);
                    continue;
                }

                if (operation < (num - middle)) {
                    operationFlag = false;
                    break;
                }

                operation -= (num - middle);
            }

            if (operationFlag == false) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

#elif (AVERAGE)
        cout << "AVERAGE\n";

        // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
        int prefixSumSize = nums.size();
        /* use long to avoid signed integer overflow
         *  n == nums.length
         *  2 <= n <= 10^5
         *  0 <= nums[i] <= 10^9
         */
        vector<long> prefixSum(prefixSumSize, 0);

        prefixSum[0] = nums[0];
        for (int i = 1; i < prefixSumSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (int i = 0; i < prefixSumSize; ++i) {
            retVal = max((long)retVal, ((prefixSum[i] + i) / (i + 1)));
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 7, 1, 6}}, {{10, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,7,1,6]
     *  Output: 5
     *
     *  Input: nums = [10,1]
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimizeArrayValue(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
