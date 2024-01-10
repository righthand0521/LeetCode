#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void moveZeroes(vector<int>& nums) {
        int numsSize = nums.size();
        int lastNonZeroFoundAt = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] != 0) {
                nums[lastNonZeroFoundAt++] = nums[i];
            }
        }
        for (int i = lastNonZeroFoundAt; i < numsSize; ++i) {
            nums[i] = 0;
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 0, 3, 12}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,0,3,12]
     *  Output: [1,3,12,0,0]
     *
     *  Input: nums = [0]
     *  Output: [0]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cSolution.moveZeroes(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
