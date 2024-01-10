#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int subarraySum(vector<int>& nums, int k) {
        int retVal = 0;

        unordered_map<int, int> prefixSumMap;
        prefixSumMap[0] = 1;

        int prefixSum = 0;
        for (auto& num : nums) {
            prefixSum += num;
            if (prefixSumMap.find(prefixSum - k) != prefixSumMap.end()) {
                retVal += prefixSumMap[prefixSum - k];
            }
            prefixSumMap[prefixSum]++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 1, 1}, 2}, {{1, 2, 3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1], k = 2
     *  Output: 2
     *
     *  Input: nums = [1,2,3], k = 3
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.subarraySum(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
