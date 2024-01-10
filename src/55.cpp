#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canJump(vector<int>& nums) {
        bool retVal = false;

        /* maxPosition is index + nums[index]
         *  If maxPosition could not reach next index, thah is, it could not reach the last index.
         */
        int maxPosition = 0;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            if (i > maxPosition) {
                return retVal;
            }

            maxPosition = max(maxPosition, i + nums[i]);
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 1, 1, 4}}, {{3, 2, 1, 0, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,1,1,4]
     *  Output: true
     *
     *  Input: nums = [3,2,1,0,4]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.canJump(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
