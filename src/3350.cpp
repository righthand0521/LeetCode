#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int current = 1;
        int previous = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > nums[i - 1]) {
                current += 1;
            } else {
                previous = current;
                current = 1;
            }
            retVal = max(retVal, min(previous, current));
            retVal = max(retVal, current / 2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 5, 7, 8, 9, 2, 3, 4, 3, 1}}, {{1, 2, 3, 4, 4, 4, 4, 5, 6, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,5,7,8,9,2,3,4,3,1]
     *  Output: 3
     *
     *  Input: nums = [1,2,3,4,4,4,4,5,6,7]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxIncreasingSubarrays(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
