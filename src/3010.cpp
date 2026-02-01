#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumCost(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int min1 = (nums[1] < nums[2]) ? (nums[1]) : (nums[2]);
        int min2 = (nums[1] < nums[2]) ? (nums[2]) : (nums[1]);
        for (int i = 3; i < numsSize; ++i) {
            if (nums[i] <= min1) {
                min2 = min1;
                min1 = nums[i];
            } else if (nums[i] < min2) {
                min2 = nums[i];
            }
        }
        retVal = nums[0] + min1 + min2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 12}}, {{5, 4, 3}}, {{10, 3, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,12]
     *  Output: 6
     *
     *  Input: nums = [5,4,3]
     *  Output: 12
     *
     *  Input: nums = [10,3,1,1]
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumCost(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
