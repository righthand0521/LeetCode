#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums, int x) {
        int retVal = -1;

        int target = accumulate(nums.begin(), nums.end(), 0) - x;
        if (target < 0) {
            return retVal;
        }

        /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
         *  sum(fragment of nums) = sum(nums) - x
         *  Example
         *  +-------------------+   +----------------------------+
         *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
         *  | = 11-5    |       |   |       | =30-10 |           |
         *  +-------------------+   +----------------------------+
         *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
         *  +-------------------+   +----------------------------+
         */
        int numsSize = nums.size();
        int sum = 0;
        int start = 0;
        for (int tail = 0; tail < numsSize; ++tail) {
            sum += nums[tail];
            while (sum > target) {
                sum -= nums[start++];
            }

            if (sum == target) {
                retVal = max(retVal, tail - start + 1);
            }
        }

        if (retVal != -1) {
            retVal = numsSize - retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int x;
    };
    vector<subject> testData{{{1, 1, 4, 2, 3}, 5}, {{5, 6, 7, 8, 9}, 4}, {{3, 2, 20, 1, 1, 3}, 10}, {{1, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,4,2,3], x = 5
     *  Output: 2
     *
     *  Input: nums = [5,6,7,8,9], x = 4
     *  Output: -1
     *
     *  Input: nums = [3,2,20,1,1,3], x = 10
     *  Output: 5
     *
     *  Input: nums = [1,1], x = 3
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], x = " << testData[i].x << "\n";

        answer = cSolution.minOperations(testData[i].nums, testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
