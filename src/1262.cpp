#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSumDivThree(vector<int>& nums) {
        int retVal = 0;

        vector<int> dp = {0, numeric_limits<int>::min(), numeric_limits<int>::min()};
        for (int num : nums) {
            vector<int> tmp = dp;
            for (int i = 0; i < 3; ++i) {
                tmp[(i + num % 3) % 3] = max(tmp[(i + num % 3) % 3], dp[i] + num);
            }
            dp = move(tmp);
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 6, 5, 1, 8}}, {{4}}, {{1, 2, 3, 4, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,6,5,1,8]
     *  Output: 18
     *
     *  Input: nums = [4]
     *  Output: 0
     *
     *  Input: nums = [1,2,3,4,4]
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

        answer = cSolution.maxSumDivThree(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
