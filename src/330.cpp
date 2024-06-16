#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minPatches(vector<int>& nums, int n) {
        int retVal = 0;

        int numsSize = nums.size();
        int index = 0;
        long x = 1;
        while (x <= n) {
            if ((index < numsSize) && (nums[index] <= x)) {
                x += nums[index];
                index += 1;
            } else {
                x <<= 1;
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int n;
    };
    vector<subject> testData{{{1, 3}, 6}, {{1, 5, 10}, 20}, {{1, 2, 2}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3], n = 6
     *  Output: 1
     *
     *  Input: nums = [1,5,10], n = 20
     *  Output: 2
     *
     *  Input: nums = [1,2,2], n = 5
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], n = " << testData[i].n << "\n";

        answer = cSolution.minPatches(testData[i].nums, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
