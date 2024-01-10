#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int reductionOperations(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int count = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] != nums[i - 1]) {
                count += 1;
            }
            retVal += count;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 1, 3}}, {{1, 1, 1}}, {{1, 1, 2, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,1,3]
     *  Output: 3
     *
     *  Input: nums = [1,1,1]
     *  Output: 0
     *
     *  Input: nums = [1,1,2,2,3]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.reductionOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
