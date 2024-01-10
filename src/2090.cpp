#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
        vector<long long> prefixSum(numsSize + 1, 0);
        for (int i = 0; i < numsSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        retVal.resize(numsSize, -1);
        for (int i = k; i < numsSize - k; ++i) {
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{7, 4, 3, 9, 1, 8, 5, 2, 6}, 3}, {{100000}, 0}, {{8}, 100000}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
     *  Output: [-1,-1,-1,5,4,4,-1,-1,-1]
     *
     *  Input: nums = [100000], k = 0
     *  Output: [100000]
     *
     *  Input: nums = [8], k = 100000
     *  Output: [-1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.getAverages(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
