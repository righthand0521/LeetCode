#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumDifference(vector<int>& nums) {
        int retVal = -1;  // If no such i and j exists, return -1.

        int numsSize = nums.size();

        int minNum = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > minNum) {
                retVal = max(retVal, nums[i] - minNum);
            } else {
                minNum = nums[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{7, 1, 5, 4}}, {{9, 4, 3, 2}}, {{1, 5, 2, 10}}, {{9, 4, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [7,1,5,4]
     *  Output: 4
     *
     *  Input: nums = [9,4,3,2]
     *  Output: -1
     *
     *  Input: nums = [1,5,2,10]
     *  Output: 9
     *
     *  Input: nums = [9,4,4]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maximumDifference(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
