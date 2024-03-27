#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int retVal = 0;

        /* the product of nums could not be strictly less than 1
         *  1 <= nums.length <= 3 * 10^4
         *  1 <= nums[i] <= 1000
         *  0 <= k <= 10^6
         */
        if (k <= 1) {
            return retVal;
        }

        /* Sliding window with Two Pointer
         *  +--------------------------------------------+
         *  |    0   |      1      |   2   |      3      |
         *  +--------------------------------------------+
         *  |   10   |      5      |   2   |      6      |
         *  +--------------------------------------------+
         *  |  right -1-> right -2-> right -4-> right    |
         *  |  left  -3-> left                           |
         *  +--------------------------------------------+
         *  | product = 10                               |
         *  | product = 50, product = 100                |
         *  | product = 10                               |
         *  | product = 60                               |
         *  +--------------------------------------------+
         */
        int numsSize = nums.size();
        int product = 1;
        int right = 0;
        int left = 0;
        for (right = 0; right < numsSize; right++) {
            product *= nums[right];
            while (product >= k) {
                product /= nums[left];
                left++;
            }
            retVal += (right - left + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{10, 5, 2, 6}, 100}, {{1, 2, 3}, 0}, {{1, 1, 1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,5,2,6], k = 100
     *  Output: 8
     *
     *  Input: nums = [1,2,3], k = 0
     *  Output: 0
     *
     *  Input: nums = [1,1,1], k = 1
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

        answer = cSolution.numSubarrayProductLessThanK(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
