#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countValidPairs(vector<int>& nums, int threshold) {
        int retVal = 0;

        int index = 0;
        int numsSize = nums.size();
        while (index < numsSize - 1) {
            // If a valid pair is found, skip both numbers.
            if (nums[index + 1] - nums[index] <= threshold) {
                retVal += 1;
                index += 1;
            }
            index += 1;
        }

        return retVal;
    }
    int minimizeMax(vector<int>& nums, int p) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = nums[numsSize - 1] - nums[0];
        while (left < right) {
            int middle = left + (right - left) / 2;
            // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
            if (countValidPairs(nums, middle) >= p) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int p;
    };
    vector<subject> testData{{{10, 1, 2, 7, 1, 3}, 2}, {{4, 2, 1, 2}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,1,2,7,1,3], p = 2
     *  Output: 1
     *
     *  Input: nums = [4,2,1,2], p = 1
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], p = " << testData[i].p << "\n";

        answer = cSolution.minimizeMax(testData[i].nums, testData[i].p);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
