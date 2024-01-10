#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        /* Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
         *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
         *  | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
         *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
         */
        int numsSize = nums.size();
        k %= numsSize;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, 7}, 3}, {{-1, -100, 3, 99}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,5,6,7], k = 3
     *  Output: [5,6,7,1,2,3,4]
     *
     *  Input: nums = [-1,-100,3,99], k = 2
     *  Output: [3,99,-1,-100]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        cSolution.rotate(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
