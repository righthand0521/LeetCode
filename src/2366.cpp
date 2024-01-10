#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minimumReplacement(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = numsSize - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) {
                continue;
            }

            long long operations = (nums[i] + nums[i + 1] - 1LL) / nums[i + 1];
            retVal += (operations - 1);
            nums[i] = nums[i] / operations;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 9, 3}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,9,3]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4,5]
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

        answer = cSolution.minimumReplacement(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
