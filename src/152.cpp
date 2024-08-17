#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        int retVal = numeric_limits<int>::min();

        double tmp;
        double maxValue = 1;
        double minValue = 1;
        for (int num : nums) {
            /* Dynamic Programming
             *  keep max = MAX(max, nums[i])
             *  keep min = MIN(min, nums[i]) because -10 <= nums[i] <= 10
             *  swap max and min if nums[i] < 0
             *
             *  Example
             *   nums[] = {2, 3, -2, 4}
             *   nums[0]=2: keep max=2, min=2; retVal=2.
             *   nums[1]=3: keep max=6, min=3; retVal=6.
             *   nums[2]=-2: swap max=3, min=6; keep max=-2, min=-12; retVal=6.
             *   nums[3]=4: keep max=4, min=-48; retVal=6.
             */
            if (num < 0) {
                tmp = maxValue;
                maxValue = minValue;
                minValue = tmp;
            }
            tmp = maxValue * num;
            maxValue = max((double)num, tmp);
            tmp = minValue * num;
            minValue = min((double)num, tmp);
            retVal = max((double)retVal, maxValue);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, -2, 4}}, {{-2, 0, -1}}, {{0,  10, 10, 10, 10, 10, 10, 10, 10, 10, -10,
                                                               10, 10, 10, 10, 10, 10, 10, 10, 10, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,-2,4]
     *  Output: 6
     *
     *  Input: nums = [-2,0,-1]
     *  Output: 0
     *
     *  Input: nums = [0,10,10,10,10,10,10,10,10,10,-10,10,10,10,10,10,10,10,10,10,0]
     *  Output: 1000000000]
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxProduct(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
