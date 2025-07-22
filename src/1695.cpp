#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> prefixsum(numsSize + 1);
        unordered_map<int, int> frequency;
        int previous = 0;
        for (int i = 0; i < numsSize; ++i) {
            prefixsum[i + 1] = prefixsum[i] + nums[i];
            previous = max(previous, frequency[nums[i]]);
            retVal = max(retVal, prefixsum[i + 1] - prefixsum[previous]);
            frequency[nums[i]] = i + 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 2, 4, 5, 6}}, {{5, 2, 1, 2, 5, 2, 1, 2, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,2,4,5,6]
     *  Output: 17
     *
     *  Input: nums = [5,2,1,2,5,2,1,2,5]
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maximumUniqueSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
