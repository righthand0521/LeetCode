#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMiddleIndex(vector<int>& nums) {
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
    vector<subject> testData{{{2, 3, -1, 8, 4}}, {{1, -1, 4}}, {{2, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,-1,8,4]
     *  Output: 3
     *
     *  Input: nums = [1,-1,4]
     *  Output: 2
     *
     *  Input: nums = [2,5]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMiddleIndex(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
