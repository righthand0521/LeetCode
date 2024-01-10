#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int searchInsert(vector<int>& nums, int target) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{1, 3, 5, 6}, 5}, {{1, 3, 5, 6}, 2}, {{1, 3, 5, 6}, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,5,6], target = 5
     *  Output: 2
     *
     *  Input: nums = [1,3,5,6], target = 2
     *  Output: 1
     *
     *  Input: nums = [1,3,5,6], target = 7
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.searchInsert(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
