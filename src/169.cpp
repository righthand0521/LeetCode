#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int majorityElement(vector<int>& nums) {
        int retVal = 0;

        /* Boyer–Moore majority vote algorithm
         *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
         *
         *  Example: Input: nums = [2,2,1,1,1,2,2]
         *  +-----------+---------------------------+
         *  | nums      | 2 | 2 | 1 | 1 | 1 | 2 | 2 |
         *  | appears   | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
         *  |-----------+---------------------------+
         *  | candidate | 2 | 2 | 2 | 2 | 1 | 1 | 2 |
         *  | count     | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
         *  +-----------+---------------------------+
         */
        int appears = 0;
        for (int num : nums) {
            if (appears == 0) {
                retVal = num;
            }

            if (retVal == num) {
                ++appears;
            } else {
                --appears;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 2, 3}}, {{2, 2, 1, 1, 1, 2, 2}}, {{3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,3]
     *  Output: 3
     *
     *  Input: nums = [2,2,1,1,1,2,2]
     *  Output: 2
     *
     *  Input: nums = [3]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.majorityElement(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
