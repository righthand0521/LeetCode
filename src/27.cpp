#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int removeElement(vector<int>& nums, int val) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] != val) {
                nums[retVal++] = nums[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int val;
    };
    vector<subject> testData{{{3, 2, 2, 3}, 3}, {{0, 1, 2, 2, 3, 0, 4, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,2,3], val = 3
     *  Output: 2, nums = [2,2,_,_]
     *
     *  Input: nums = [0,1,2,2,3,0,4,2], val = 2
     *  Output: 5, nums = [0,1,4,0,3,_,_,_]
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], val = " << testData[i].val << "\n";

        answer = cSolution.removeElement(testData[i].nums, testData[i].val);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
