#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal.emplace_back(1);
        }

        /*
         *   1  2  3  4
         *  x1 24 12  4 => 1 x 24 = 24
         *   1 x1 12  4 => 1 x 12 = 12
         *   1  2 x1  4 => 2 x  4 =  8
         *   1  2  6 x1 => 6 x  1 =  6
         */
        for (int i = 1; i < numsSize; ++i) {
            retVal[i] = retVal[i - 1] * nums[i - 1];
        }
        int tmp = 1;
        for (int i = numsSize - 2; i >= 0; --i) {
            tmp *= nums[i + 1];
            retVal[i] *= tmp;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{-1, 1, 0, -3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: [24,12,8,6]
     *
     *  Input: nums = [-1,1,0,-3,3]
     *  Output: [0,0,9,0,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.productExceptSelf(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
