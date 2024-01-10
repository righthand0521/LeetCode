#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<unordered_map<long long, int>> dp(numsSize);
        for (int i = 0; i < numsSize; ++i) {
            for (int j = 0; j < i; ++j) {
                long long diff = (long long)nums[i] - (long long)nums[j];

                int count = 0;
                auto iterator = dp[j].find(diff);
                if (iterator != dp[j].end()) {
                    count = iterator->second;
                }
                retVal += count;

                dp[i][diff] += (count + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 4, 6, 8, 10}}, {{7, 7, 7, 7, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,4,6,8,10]
     *  Output: 7
     *
     *  Input: nums = [7,7,7,7,7]
     *  Output: 16
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.numberOfArithmeticSlices(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
