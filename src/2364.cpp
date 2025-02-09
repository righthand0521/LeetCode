#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countBadPairs(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> diffCount;
        for (int pos = 0; pos < numsSize; pos++) {
            int diff = pos - nums[pos];
            int goodPairsCount = diffCount[diff];  // Count of previous positions with same difference
            retVal += (pos - goodPairsCount);      // Total possible pairs minus good pairs = bad pairs
            diffCount[diff] = goodPairsCount + 1;  // Update count of positions with this difference
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 1, 3, 3}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,1,3,3]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countBadPairs(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
