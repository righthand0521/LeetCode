#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int initialGap = 0;
        int qsize = 0;
        int start = 0;
        for (int end = 0; end < numsSize; ++end) {
            // If current element is odd, increment qsize by 1.
            if (nums[end] % 2 == 1) {
                qsize += 1;
            }

            if (qsize == k) {
                initialGap = 0;

                // Calculate the number of even elements in the beginning of subarray.
                while (qsize == k) {
                    qsize -= nums[start] % 2;
                    initialGap += 1;
                    start += 1;
                }
            }

            retVal += initialGap;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 1, 2, 1, 1}, 3}, {{2, 4, 6}, 1}, {{2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,2,1,1], k = 3
     *  Output: 2
     *
     *  Input: nums = [2,4,6], k = 1
     *  Output: 0
     *
     *  Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
     *  Output: 16
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.numberOfSubarrays(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
