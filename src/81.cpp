#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool search(vector<int>& nums, int target) {
        bool retVal = false;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                retVal = true;
                break;
            } else if ((nums[middle] == nums[left]) && (nums[middle] == nums[right])) {
                left += 1;
                right -= 1;
            } else if (nums[middle] >= nums[left]) {
                if ((target >= nums[left]) && (target < nums[middle])) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            } else {
                if ((target <= nums[right]) && (target > nums[middle])) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
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
    vector<subject> testData{{{2, 5, 6, 0, 0, 1, 2}, 0}, {{2, 5, 6, 0, 0, 1, 2}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,5,6,0,0,1,2], target = 0
     *  Output: true
     *
     *  Input: nums = [2,5,6,0,0,1,2], target = 3
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.search(testData[i].nums, testData[i].target);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
