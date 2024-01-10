#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> retVal;

        /* Boyer–Moore majority vote algorithm
         *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
         */
        int candidate1 = 0;
        int count1 = 0;
        int candidate2 = 0;
        int count2 = 0;
        for (int num : nums) {
            if ((count1 > 0) && (candidate1 == num)) {
                ++count1;
            } else if ((count2 > 0) && (candidate2 == num)) {
                ++count2;
            } else if (count1 == 0) {
                candidate1 = num;
                ++count1;
            } else if (count2 == 0) {
                candidate2 = num;
                ++count2;
            } else {
                --count1;
                --count2;
            }
        }

        int check1 = 0;
        int check2 = 0;
        for (int num : nums) {
            if ((num == candidate1) && (count1 > 0)) {
                ++check1;
            } else if ((num == candidate2) && (count2 > 0)) {
                ++check2;
            }
        }

        int numsSize = nums.size();
        if (check1 > numsSize / 3) {
            retVal.emplace_back(candidate1);
        }
        if (check2 > numsSize / 3) {
            retVal.emplace_back(candidate2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{3, 2, 3}}, {{1}}, {{1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,3]
     *  Output: [3]
     *
     *  Input: nums = [1]
     *  Output: [1]
     *
     *  Input: nums = [1,2]
     *  Output: [1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.majorityElement(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
