#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();

        unordered_map<int, int> numToIndex;
        long long currentSum = 0;
        int begin = 0;
        int end = 0;
        while (end < numsSize) {
            int currNum = nums[end];
            int lastOccurrence = (numToIndex.count(currNum) ? numToIndex[currNum] : -1);

            // if current window already has number or if window is too big, adjust window
            while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
                currentSum -= nums[begin];
                begin++;
            }

            numToIndex[currNum] = end;
            currentSum += nums[end];
            if (end - begin + 1 == k) {
                retVal = max(retVal, currentSum);
            }

            end++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 5, 4, 2, 9, 9, 9}, 3}, {{4, 4, 4}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,5,4,2,9,9,9], k = 3
     *  Output: 15
     *
     *  Input: nums = [4,4,4], k = 3
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumSubarraySum(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
