#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void nextPermutation(vector<int>& nums) {
        int numsSize = nums.size();

        int i, j;
        for (i = numsSize - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                break;
            }
        }
        if (i < 0) {
            reverse(nums.begin(), nums.end());
        } else {
            for (j = numsSize - 1; j > i; --j) {
                if (nums[j] > nums[i]) {
                    break;
                }
            }
            swap(nums[i], nums[j]);
            reverse(nums.begin() + i + 1, nums.end());
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{3, 2, 1}}, {{1, 1, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [1,3,2]
     *
     *  Input: nums = [3,2,1]
     *  Output: [1,2,3]
     *
     *  Input: nums = [1,1,5]
     *  Output: [1,5,1]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cSolution.nextPermutation(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
