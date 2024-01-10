#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int pivotIndex(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<int> sumLeft(numsSize, 0);
        sumLeft[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            sumLeft[i] = sumLeft[i - 1] + nums[i];
        }

        vector<int> sumRight(numsSize, 0);
        sumRight[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i) {
            sumRight[i] = sumRight[i + 1] + nums[i];
        }

        for (int i = 0; i < numsSize; ++i) {
            if (sumLeft[i] == sumRight[i]) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 7, 3, 6, 5, 6}}, {{1, 2, 3}}, {{2, 1, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,7,3,6,5,6]
     *  Output: 3
     *
     *  Input: nums = [1,2,3]
     *  Output: -1
     *
     *  Input: nums = [2,1,-1]
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

        answer = cSolution.pivotIndex(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
