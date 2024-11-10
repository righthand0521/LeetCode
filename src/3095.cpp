#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if ((number >> bitPosition) & 1) {
                bitCounts[bitPosition] += delta;
            }
        }
    }
    int convertBitCountsToNumber(const vector<int>& bitCounts) {
        int retVal = 0;

        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if (bitCounts[bitPosition] != 0) {
                retVal |= (1 << bitPosition);
            }
        }

        return retVal;
    }

   public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int retVal = -1;

        int numsSize = nums.size();
        int windowStart = 0;
        vector<int> bitCounts(32, 0);
        int minLength = numeric_limits<int>::max();
        for (int windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
            updateBitCounts(bitCounts, nums[windowEnd], 1);

            while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts) >= k)) {
                minLength = min(minLength, windowEnd - windowStart + 1);
                updateBitCounts(bitCounts, nums[windowStart], -1);
                windowStart++;
            }
        }

        if (minLength != numeric_limits<int>::max()) {
            retVal = minLength;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 3}, 2}, {{2, 1, 8}, 10}, {{1, 2}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3], k = 2
     *  Output: 1
     *
     *  Input: nums = [2,1,8], k = 10
     *  Output: 3
     *
     *  Input: nums = [1,2], k = 0
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

        answer = cSolution.minimumSubarrayLength(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
