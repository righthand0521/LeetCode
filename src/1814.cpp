#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)

   public:
    int reverseInteger(int num) {
        int retVal = 0;

        while (num > 0) {
            retVal = retVal * 10 + num % 10;
            num /= 10;
        }

        return retVal;
    }
    int countNicePairs(vector<int>& nums) {
        int retVal = 0;

        /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
         * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
         */
        unordered_map<int, int> hashTable;
        for (int num : nums) {
            int reverse = reverseInteger(num);

            retVal = (retVal + hashTable[num - reverse]) % MODULO;
            ++hashTable[num - reverse];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{42, 11, 1, 97}}, {{13, 10, 35, 24, 76}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [42,11,1,97]
     *  Output: 2
     *
     *  Input: nums = [13,10,35,24,76]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countNicePairs(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
