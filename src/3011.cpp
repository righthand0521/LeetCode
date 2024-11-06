#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canSortArray(vector<int>& nums) {
        bool retVal = true;

        int lastCnt = 0;
        int lastGroupMax = 0;
        int curGroupMax = 0;
        for (int num : nums) {
            int curCnt = __builtin_popcount(num);
            if (curCnt == lastCnt) {
                curGroupMax = max(curGroupMax, num);
            } else {
                lastCnt = curCnt;
                lastGroupMax = curGroupMax;
                curGroupMax = num;
            }

            if (num < lastGroupMax) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{8, 4, 2, 30, 15}}, {{1, 2, 3, 4, 5}}, {{3, 16, 8, 4, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [8,4,2,30,15]
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: true
     *
     *  Input: nums = [3,16,8,4,2]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.canSortArray(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
