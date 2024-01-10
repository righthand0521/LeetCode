#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize < 2) {
            retVal = numsSize;
            return retVal;
        }

        int count = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[retVal] != nums[i]) {
                count = 0;
            } else {
                ++count;
            }

            if (count < 2) {
                retVal++;
                nums[retVal] = nums[i];
            }
        }
        retVal += 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 1, 2, 2, 3}}, {{0, 0, 1, 1, 1, 1, 2, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1,2,2,3]
     *  Output: 5, nums = [1,1,2,2,3,_]
     *
     *  Input: nums = [0,0,1,1,1,1,2,3,3]
     *  Output: 7, nums = [0,0,1,1,2,3,3,_,_]
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
        cout << "Output: " << answer << ", nums = [";
        for (int j = 0; j < answer; ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
