#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }

        for (int i = 1; i < numsSize; ++i) {
            if (nums[retVal] != nums[i]) {
                nums[++retVal] = nums[i];
            }
        }
        ++retVal;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 2}}, {{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,2]
     *  Output: 2, nums = [1,2,_]
     *
     *  Input: nums = [0,0,1,1,1,2,2,3,3,4]
     *  Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.removeDuplicates(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
