#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int triangularSum(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        while (numsSize > 1) {
            vector<int> newNums;
            for (int i = 0; i < numsSize - 1; ++i) {
                newNums.emplace_back((nums[i] + nums[i + 1]) % 10);
            }
            nums = move(newNums);
            numsSize = nums.size();
        }
        retVal = nums[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: 8
     *
     *  Input: nums = [5]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.triangularSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
