#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = 0;

        for (int num : nums) {
            retVal += num;
        }
        retVal %= k;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{3, 9, 7}, 5}, {{4, 1, 3}, 4}, {{3, 2}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,9,7], k = 5
     *  Output: 4
     *
     *  Input: nums = [4,1,3], k = 4
     *  Output: 0
     *
     *  Input: nums = [3,2], k = 6
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minOperations(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
