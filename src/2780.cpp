#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumIndex(vector<int>& nums) {
        int retVal = -1;  // If no valid split exists, return -1.

        // Find the majority element
        int x = nums[0];
        int count = 0;
        for (auto& num : nums) {
            if (num == x) {
                count++;
            } else {
                count--;
            }

            if (count == 0) {
                x = num;
                count = 1;
            }
        }

        // Count frequency of majority element
        int xCount = 0;
        for (auto& num : nums) {
            if (num == x) {
                xCount++;
            }
        }

        // Check if valid split is possible
        count = 0;
        int numsSize = nums.size();
        for (int index = 0; index < numsSize; index++) {
            if (nums[index] == x) {
                count++;
            }

            int remainingCount = xCount - count;

            if ((count * 2 > index + 1) && (remainingCount * 2 > numsSize - index - 1)) {
                retVal = index;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 2}}, {{2, 1, 3, 1, 1, 1, 7, 1, 2, 1}}, {{3, 3, 3, 3, 7, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,2]
     *  Output: 2
     *
     *  Input: nums = [2,1,3,1,1,1,7,1,2,1]
     *  Output: 4
     *
     *  Input: nums = [3,3,3,3,7,2,2]
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

        answer = cSolution.minimumIndex(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
