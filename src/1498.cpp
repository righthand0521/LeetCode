#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numSubseq(vector<int>& nums, int target) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<int> pows(numsSize, 1);
        for (int i = 1; i < numsSize; ++i) {
            pows[i] = pows[i - 1] * 2 % MODULO;
        }

        sort(nums.begin(), nums.end());
        int head = 0;
        int tail = numsSize - 1;
        while (head <= tail) {
            if (nums[head] + nums[tail] > target) {
                --tail;
                continue;
            }

            retVal += pows[tail - head];
            retVal %= MODULO;
            ++head;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{3, 5, 6, 7}, 9}, {{3, 3, 6, 8}, 10}, {{2, 3, 3, 4, 6, 7}, 12}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,5,6,7], target = 9
     *  Output: 4
     *
     *  Input: nums = [3,3,6,8], target = 10
     *  Output: 6
     *
     *  Input: nums = [2,3,3,4,6,7], target = 12
     *  Output: 61
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.numSubseq(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
