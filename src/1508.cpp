#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> numsSum;
        for (int start = 0; start < numsSize; ++start) {
            int sum = 0;
            for (int idx = start; idx < numsSize; ++idx) {
                sum += nums[idx];
                numsSum.emplace_back(sum);
            }
        }
        sort(numsSum.begin(), numsSum.end());

        for (int idx = left - 1; idx < right; ++idx) {
            retVal += numsSum[idx];
            retVal %= MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int n;
        int left;
        int right;
    };
    vector<subject> testData{{{1, 2, 3, 4}, 4, 1, 5}, {{1, 2, 3, 4}, 4, 3, 4}, {{1, 2, 3, 4}, 4, 1, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
     *  Output: 13
     *
     *  Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
     *  Output: 6
     *
     *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
     *  Output: 50
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "] , n = " << testData[i].n;
        cout << ", left = " << testData[i].left << ", right = " << testData[i].right << "\n";

        answer = cSolution.rangeSum(testData[i].nums, testData[i].n, testData[i].left, testData[i].right);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
