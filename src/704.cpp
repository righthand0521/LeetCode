#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int retVal = -1;

        int numsSize = nums.size();

        int mid = 0;
        int low = 0;
        int high = numsSize - 1;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                retVal = mid;
                break;
            }

            if (nums[mid] > target) {
                high = mid - 1;
            } else if (nums[mid] < target) {
                low = mid + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{-1, 0, 3, 5, 9, 12}, 9},
                             {{-1, 0, 3, 5, 9, 12}, 2},
                             {{5}, 5},
                             {{5}, 2},
                             {{2, 5}, 2},
                             {{2, 5}, 5},
                             {{2, 5}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-1,0,3,5,9,12], target = 9
     *  Output: 4
     *
     *  Input: nums = [-1,0,3,5,9,12], target = 2
     *  Output: -1
     *
     *  Input: nums = [5], target = 5
     *  Output: 0
     *
     *  Input: nums = [5], target = 2
     *  Output: -1
     *
     *  Input: nums = [2,5], target = 2
     *  Output: 0
     *
     *  Input: nums = [2,5], target = 5
     *  Output: 1
     *
     *  Input: nums = [2,5], target = 0
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.search(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
