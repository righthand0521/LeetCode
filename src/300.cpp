#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)
class Solution {
   public:
    Solution() {
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "DYNAMIC_PROGRAMMING\n";
#endif
        cout << "\n";
    }
    int lengthOfLIS(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }

#if (BINARY_SEARCH)
        vector<int> greedy(numsSize + 1, 0);
        int idx = 1;
        greedy[idx] = nums[0];

        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > greedy[idx]) {
                greedy[++idx] = nums[i];
                continue;
            }

            int left = 1;
            int right = idx;
            int position = 0;
            while (left < right) {
                int middle = left + (right - left) / 2;
                if (greedy[middle] < nums[i]) {
                    position = middle;
                    left = middle + 1;
                } else {
                    right = middle;
                }
            }
            greedy[position + 1] = nums[i];
        }
        retVal = idx;
#elif (DYNAMIC_PROGRAMMING)
        vector<int> dp(numsSize, 0);
        for (int i = 0; i < numsSize; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        retVal = *max_element(dp.begin(), dp.end());
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 9, 2, 5, 3, 7, 101, 18}}, {{0, 1, 0, 3, 2, 3}}, {{7, 7, 7, 7, 7, 7, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,9,2,5,3,7,101,18]
     *  Output: 4
     *
     *  Input: nums = [0,1,0,3,2,3]
     *  Output: 4
     *
     *  Input: nums = [7,7,7,7,7,7,7]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.lengthOfLIS(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
