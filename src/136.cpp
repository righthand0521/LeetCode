#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int retVal = 0;

        for (auto num : nums) {
            retVal ^= num;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 2, 1}}, {{4, 1, 2, 1, 2}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,2,1]
     *  Output: 1
     *
     *  Input: nums = [4,1,2,1,2]
     *  Output: 4
     *
     *  Input: nums = [1]
     *  Output: 1
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
