#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        long long retVal = 0;

        unordered_map<int, int> hashTable;
        hashTable[0] = 1;

        int prefix = 0;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] % modulo == k) {
                prefix++;
            }
            retVal += hashTable[(prefix - k + modulo) % modulo];
            hashTable[prefix % modulo]++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int modulo;
        int k;
    };
    vector<subject> testData{{{3, 2, 4}, 2, 1}, {{3, 1, 9, 6}, 3, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,4], modulo = 2, k = 1
     *  Output: 3
     *
     *  Input: nums = [3,1,9,6], modulo = 3, k = 0
     *  Output: 2
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], modulo = " << testData[i].modulo << ", k = " << testData[i].k << "\n";

        answer = cSolution.countInterestingSubarrays(testData[i].nums, testData[i].modulo, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
