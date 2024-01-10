#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long retVal = 0;

        int contiguous = 0;
        for (auto num : nums) {
            if (num != 0) {
                contiguous = 0;
                continue;
            }

            ++contiguous;
            retVal += contiguous;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 0, 0, 2, 0, 0, 4}}, {{0, 0, 0, 2, 0, 0}}, {{2, 10, 2019}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,0,0,2,0,0,4]
     *  Output: 6
     *
     *  Input: nums = [0,0,0,2,0,0]
     *  Output: 9
     *
     *  Input: nums = [2,10,2019]
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.zeroFilledSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
