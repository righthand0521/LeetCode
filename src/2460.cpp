#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> applyOperations(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        int writeIndex = 0;  // Pointer to place non-zero elements
        for (int index = 0; index < numsSize; index++) {
            // Step 1: Merge adjacent equal elements if they are non-zero
            if ((index < numsSize - 1) && (nums[index] == nums[index + 1]) && (nums[index] != 0)) {
                nums[index] *= 2;
                nums[index + 1] = 0;
            }

            // Step 2: Shift non-zero elements to the front
            if (nums[index] != 0) {
                if (index != writeIndex) {
                    swap(nums[index], nums[writeIndex]);
                }
                writeIndex++;
            }
        }
        retVal = nums;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 1, 1, 0}}, {{0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,1,1,0]
     *  Output: [1,4,2,0,0,0]
     *
     *  Input: nums = [0,1]
     *  Output: [1,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.applyOperations(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
