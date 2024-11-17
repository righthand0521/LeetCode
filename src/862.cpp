#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int shortestSubarray(vector<int>& nums, int k) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<long long> prefixSums(numsSize + 1, 0);
        for (int i = 1; i <= numsSize; i++) {
            prefixSums[i] = prefixSums[i - 1] + nums[i - 1];
        }

        deque<int> candidateIndices;
        int shortestSubarrayLength = numeric_limits<int>::max();
        for (int i = 0; i <= numsSize; i++) {
            // Remove candidates from front of deque where subarray sum meets target
            while ((candidateIndices.empty() == false) && (prefixSums[i] - prefixSums[candidateIndices.front()] >= k)) {
                shortestSubarrayLength = min(shortestSubarrayLength, i - candidateIndices.front());
                candidateIndices.pop_front();
            }

            // Maintain monotonicity by removing indices with larger prefix sums
            while ((candidateIndices.empty() == false) && (prefixSums[i] <= prefixSums[candidateIndices.back()])) {
                candidateIndices.pop_back();
            }

            // Add current index to candidates
            candidateIndices.push_back(i);
        }

        if (shortestSubarrayLength != numeric_limits<int>::max()) {
            retVal = shortestSubarrayLength;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1}, 1}, {{1, 2}, 4}, {{2, -1, 2}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1], k = 1
     *  Output: 1
     *
     *  Input: nums = [1,2], k = 4
     *  Output: -1
     *
     *  Input: nums = [2,-1,2], k = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.shortestSubarray(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
