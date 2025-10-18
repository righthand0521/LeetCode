#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int previous = numeric_limits<int>::min();
        int current;
        for (const auto& num : nums) {
            current = min(max(num - k, previous + 1), num + k);
            if (current > previous) {
                retVal += 1;
                previous = current;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 2, 3, 3, 4}, 2}, {{4, 4, 4, 4}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,3,3,4], k = 2
     *  Output: 6
     *
     *  Input: nums = [4,4,4,4], k = 1
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxDistinctElements(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
