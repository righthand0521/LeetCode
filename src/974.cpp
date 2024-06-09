#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int retVal = 0;

        vector<int> modRecord(k, 0);
        modRecord[0] = 1;

        int prefixSumMod = 0;
        for (int num : nums) {
            prefixSumMod = (prefixSumMod + num % k + k) % k;
            retVal += modRecord[prefixSumMod];
            modRecord[prefixSumMod]++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{4, 5, 0, -2, -3, 1}, 5}, {{5}, 9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,5,0,-2,-3,1], k = 5
     *  Output: 7
     *
     *  Input: nums = [5], k = 9
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.subarraysDivByK(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
