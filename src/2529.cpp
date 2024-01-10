#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumCount(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int negative = 0;
        int zero = 0;
        int positive = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] < 0) {
                ++negative;
            } else if (nums[i] == 0) {
                ++zero;
            } else {
                break;
            }
        }
        positive = numsSize - negative - zero;

        retVal = max(negative, positive);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-2, -1, -1, 1, 2, 3}}, {{-3, -2, -1, 0, 0, 1, 2}}, {{5, 20, 66, 1314}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-2,-1,-1,1,2,3]
     *  Output: 3
     *
     *  Input: nums = [-3,-2,-1,0,0,1,2]
     *  Output: 3
     *
     *  Input: nums = [5,20,66,1314]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maximumCount(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
