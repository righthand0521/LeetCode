#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> retVal;

        int numsSize = nums.size();

        int idx = 0;
        while (idx < numsSize) {
            int tmp = nums[idx];
            while ((idx + 1 < numsSize) && (nums[idx] + 1 == nums[idx + 1])) {
                ++idx;
            }

            if (tmp == nums[idx]) {
                retVal.emplace_back(to_string(tmp));
            } else {
                retVal.emplace_back(to_string(tmp) + "->" + to_string(nums[idx]));
            }

            ++idx;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 2, 4, 5, 7}}, {{0, 2, 3, 4, 6, 8, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,2,4,5,7]
     *  Output: ["0->2","4->5","7"]
     *
     *  Input: nums = [0,2,3,4,6,8,9]
     *  Output: ["0","2->4","6","8->9"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.summaryRanges(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
