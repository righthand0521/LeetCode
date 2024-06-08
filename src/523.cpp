#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        bool retVal = false;

        int prefixMod = 0;
        unordered_map<int, int> modSeen;
        modSeen[0] = -1;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            prefixMod = (prefixMod + nums[i]) % k;
            if (modSeen.find(prefixMod) != modSeen.end()) {  // ensures that the size of subarray is atleast 2
                if (i - modSeen[prefixMod] > 1) {
                    retVal = true;
                    break;
                }
            } else {  // mark the value of prefixMod with the current index.
                modSeen[prefixMod] = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{23, 2, 4, 6, 7}, 6}, {{23, 2, 6, 4, 7}, 6}, {{23, 2, 6, 4, 7}, 13}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: nums = [23,2,4,6,7], k = 6
     *  Output: true
     *
     *  Input: nums = [23,2,6,4,7], k = 6
     *  Output: true
     *
     *  Input: nums = [23,2,6,4,7], k = 13
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.checkSubarraySum(testData[i].nums, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
