#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSum(vector<int>& nums) {
        int retVal = 0;

        unordered_set<int> positiveNumsSet;
        for (int num : nums) {
            if (num > 0) {
                positiveNumsSet.emplace(num);
            }
        }
        if (positiveNumsSet.empty()) {
            retVal = *max_element(nums.begin(), nums.end());
        } else {
            retVal = accumulate(positiveNumsSet.begin(), positiveNumsSet.end(), 0);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{1, 1, 0, 1, 1}}, {{1, 2, -1, -2, 1, 0, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: 15
     *
     *  Input: nums = [1,1,0,1,1]
     *  Output: 1
     *
     *  Input: nums = [1,2,-1,-2,1,0,-1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
