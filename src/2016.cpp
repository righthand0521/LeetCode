#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumDifference(vector<int>& nums) {
        int retVal = -1;  // If no such i and j exists, return -1.

        // 1 <= nums[i] <= 10^9
        int minNum = 1e9 + 1;
        int maxNum = 1e9 + 1;
        for (auto num : nums) {
            if (minNum > num) {
                minNum = num;
                maxNum = num;
                continue;
            }

            if (maxNum < num) {
                maxNum = num;
            }

            retVal = max(retVal, maxNum - minNum);
        }

        // find the maximum difference between nums[i] and nums[j], such that 0 <= i < j < n and nums[i] < nums[j].
        retVal = (retVal == 0) ? -1 : retVal;

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
