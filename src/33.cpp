#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int retVal = -1;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                retVal = middle;
                break;
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
    vector<subject> testData{{{4, 5, 6, 7, 0, 1, 2}, 0}, {{4, 5, 6, 7, 0, 1, 2}, 3}, {{1}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,5,6,7,0,1,2], target = 0
     *  Output: 4
     *
     *  Input: nums = [4,5,6,7,0,1,2], target = 3
     *  Output: -1
     *
     *  Input: nums = [1], target = 0
     *  Output: -1
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
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
