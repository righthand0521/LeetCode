#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 1}}, {{1, 2, 1, 3, 5, 6, 4}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,1]
     *  Output: 2
     *
     *  Input: nums = [1,2,1,3,5,6,4]
     *  utput: 5
     *
     *  Input: nums = [1]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findPeakElement(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
