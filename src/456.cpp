#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool find132pattern(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        vector<int> minStack;
        minStack.emplace_back(nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            minStack.emplace_back(min(minStack[i - 1], nums[i]));
        }

        vector<int> middleStack;
        int middleStackSize = 0;
        for (int i = numsSize - 1; i > -1; --i) {
            if (nums[i] <= minStack[i]) {
                continue;
            }

            while ((middleStackSize > 0) && (middleStack.back() <= minStack[i])) {
                middleStack.pop_back();
                --middleStackSize;
            }

            if ((middleStackSize > 0) && (middleStack.back() < nums[i])) {
                retVal = true;
                break;
            }

            middleStack.emplace_back(nums[i]);
            ++middleStackSize;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}},    {{3, 1, 4, 2}},    {{-1, 3, 2, 0}},
                             {{1, 2, 3, 4, 0}}, {{3, 5, 0, 3, 4}}, {{2, 3, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: false
     *
     *  Input: nums = [3,1,4,2]
     *  Output: true
     *
     *  Input: nums = [-1,3,2,0]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,0]
     *  Output: false
     *
     *  Input: nums = [3,5,0,3,4]
     *  Output: true
     *
     *  Input: nums = [2,3,1,2]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.find132pattern(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
