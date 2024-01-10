#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxOperations(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());
        int numsSize = nums.size();
        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == k) {
                ++left;
                --right;
                ++retVal;
            } else if (sum < k) {
                ++left;
            } else if (sum > k) {
                --right;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4}, 5}, {{3, 1, 3, 4, 3}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4], k = 5
     *  Output: 2
     *
     *  Input: nums = [3,1,3,4,3], k = 6
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxOperations(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
