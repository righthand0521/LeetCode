#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        bool retVal = false;

        int numsSize = nums.size();

        int current = 1;
        int previous = 0;
        int answer = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > nums[i - 1]) {
                ++current;
            } else {
                previous = current;
                current = 1;
            }

            answer = max(answer, min(previous, current));
            answer = max(answer, current / 2);
        }

        retVal = (answer >= k);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 5, 7, 8, 9, 2, 3, 4, 3, 1}, 3}, {{1, 2, 3, 4, 4, 4, 4, 5, 6, 7}, 5}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
     *  Output: true
     *
     *  Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.hasIncreasingSubarrays(testData[i].nums, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
