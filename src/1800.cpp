#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxAscendingSum(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        int sum = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] >= nums[i]) {
                retVal = max(retVal, sum);
                sum = 0;
            }
            sum += nums[i];
        }
        retVal = max(retVal, sum);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 20, 30, 5, 10, 50}}, {{10, 20, 30, 40, 50}}, {{12, 17, 15, 13, 10, 11, 12}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,20,30,5,10,50]
     *  Output: 65
     *
     *  Input: nums = [10,20,30,40,50]
     *  Output: 150
     *
     *  Input: nums = [12,17,15,13,10,11,12]
     *  Output: 33
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxAscendingSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
