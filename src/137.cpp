#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int retVal = 0;

        int ones = 0;
        int twos = 0;
        for (int num : nums) {
            ones = ((ones ^ num) & (~twos));
            twos = ((twos ^ num) & (~ones));
        }
        retVal = ones;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 2, 3, 2}}, {{0, 1, 0, 1, 0, 1, 99}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,2,3,2]
     *  Output: 3
     *
     *  Input: nums = [0,1,0,1,0,1,99]
     *  Output: 99
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.singleNumber(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
