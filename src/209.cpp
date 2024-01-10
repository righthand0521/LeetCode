#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int retVal = 0;

        int len = nums.size();
        retVal = len + 1;
        int sum = 0;
        int head = 0;
        int tail;
        for (tail = 0; tail < len; ++tail) {
            sum += nums[tail];
            while (sum >= target) {
                retVal = min(retVal, tail - head + 1);

                sum -= nums[head];
                ++head;
            }
        }
        if (retVal == len + 1) {
            retVal = 0;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int target;
        vector<int> nums;
    };
    vector<subject> testData{{7, {2, 3, 1, 2, 4, 3}}, {4, {1, 4, 4}}, {11, {1, 1, 1, 1, 1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = 7, nums = [2,3,1,2,4,3]
     *  Output: 2
     *
     *  Input: target = 4, nums = [1,4,4]
     *  Output: 1
     *
     *  Input: target = 11, nums = [1,1,1,1,1,1,1,1]
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = " << testData[i].target << ", nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minSubArrayLen(testData[i].target, testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
