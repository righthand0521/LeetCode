#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSubarray(vector<int>& nums) {
        int retVal = 0;

        // The maximum possible bitwise AND should not be less than a largest element.
        // Therefore, the subarray must only include one or more largest elements.
        int maxNum = nums[0];  // 1 <= nums.length <= 10^5
        int count = 0;
        for (int num : nums) {
            if (num == maxNum) {
                count++;
                retVal = max(retVal, count);
            } else if (num > maxNum) {
                maxNum = num;
                count = 1;
                retVal = 1;
            } else if (num < maxNum) {
                count = 0;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 3, 2, 2}},
                             {{1, 2, 3, 4}},
                             {{96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 279979}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,3,2,2]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4]
     *  Output: 1
     *
     *  Input: nums = [96317,96317,96317,96317,96317,96317,96317,96317,96317,279979]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
