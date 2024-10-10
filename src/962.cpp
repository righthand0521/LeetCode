#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxWidthRamp(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> indexStack;
        indexStack.push_back(0);
        for (int i = 1; i < numsSize; ++i) {
            if (nums[indexStack.back()] > nums[i]) {
                indexStack.push_back(i);
            }
        }

        for (int i = numsSize - 1; i >= 0; --i) {
            while ((indexStack.empty() == false) && (nums[indexStack.back()] <= nums[i])) {
                retVal = max(retVal, i - indexStack.back());
                indexStack.pop_back();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{6, 0, 8, 2, 1, 5}}, {{9, 8, 1, 0, 1, 9, 4, 0, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [6,0,8,2,1,5]
     *  Output: 4
     *
     *  Input: nums = [9,8,1,0,1,9,4,0,4,1]
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxWidthRamp(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
