#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = 0;

        int xorValue = 0;
        for (int num : nums) {
            xorValue ^= num;
        }
        xorValue ^= k;
        retVal = __builtin_popcount(xorValue);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 1, 3, 4}, 1}, {{2, 0, 2, 0}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,3,4], k = 1
     *  Output: 2
     *
     *  Input: nums = [2,0,2,0], k = 0
     *  Output: 0
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
