#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int singleNonDuplicate(vector<int>& nums) {
        int retVal = 0;

        // 1 <= nums.length <= 10^5
        int len = nums.size();
        if (len == 1) {
            retVal = nums[0];
            return retVal;
        }

        int middle = 0;
        int left = 0;
        int right = len - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            /* middle is odd or even
             *  middle is odd: middle % 2 == 1
             *  +---------------------------------+
             *  |  0  | 1 | 2 | [3] | 4 | 5 |  6  |
             *  +---------------------------------+
             *  |  1  | 1 | 2 |  2  | 3 | 3 | (4) | nums[middle] == nums[middle - 1]
             *  | (1) | 2 | 2 |  3  | 3 | 4 |  4  | nums[middle] != nums[middle - 1]
             *  +---------------------------------+
             *
             *  middle is even: middle % 2 == 0
             *  +-----------------------------------------+
             *  |  0  | 1 | 2 | 3 | [4] | 5 | 6 | 7 |  8  |
             *  +-----------------------------------------+
             *  | (1) | 2 | 2 | 3 |  3  | 4 | 4 | 5 |  5  | nums[middle] == nums[middle - 1]
             *  |  1  | 1 | 2 | 2 |  3  | 3 | 4 | 4 | (5) | nums[middle] != nums[middle - 1]
             *  +-----------------------------------------+
             */
            if (middle % 2 == 1) {
                if (nums[middle] == nums[middle - 1]) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            } else {
                if (nums[middle] == nums[middle - 1]) {
                    right = middle;
                } else {
                    left = middle;
                }
            }
        }
        retVal = nums[left];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 2, 3, 3, 4, 4, 8, 8}}, {{3, 3, 7, 7, 10, 11, 11}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,2,3,3,4,4,8,8]
     *  Output: 2
     *
     *  Input: nums = [3,3,7,7,10,11,11]
     *  Output: 10
     *
     *  Input: nums = [1]
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

        answer = cSolution.singleNonDuplicate(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
