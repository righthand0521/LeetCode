#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = nums[numsSize - 1] - nums[0];
        while (left <= right) {
            int middle = (left + right) / 2;

            int index = 0;
            int i = 0;
            for (int j = 0; j < numsSize; j++) {
                while (nums[j] - nums[i] > middle) {
                    i++;
                }
                index += (j - i);
            }

            if (index >= k) {
                right = middle - 1;
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
        int k;
    };
    vector<subject> testData{{{1, 3, 1}, 1}, {{1, 1, 1}, 2}, {{1, 6, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,1], k = 1
     *  Output: 0
     *
     *  Input: nums = [1,1,1], k = 2
     *  Output: 0
     *
     *  Input: nums = [1,6,1], k = 3
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.smallestDistancePair(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
