#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> frequency;
        int start = -1;
        for (int end = 0; end < numsSize; ++end) {
            frequency[nums[end]]++;
            while (frequency[nums[end]] > k) {
                start++;
                frequency[nums[start]]--;
            }
            retVal = max(retVal, (end - start));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{
        {{1, 2, 3, 1, 2, 3, 1, 2}, 2}, {{1, 2, 1, 2, 1, 2, 1, 2}, 1}, {{5, 5, 5, 5, 5, 5, 5}, 4}, {{1, 4, 4, 3}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,1,2,3,1,2], k = 2
     *  Output: 6
     *
     *  Input: nums = [1,2,1,2,1,2,1,2], k = 1
     *  Output: 2
     *
     *  Input: nums = [5,5,5,5,5,5,5], k = 4
     *  Output: 4
     *
     *  Input: nums = [1,4,4,3], k = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxSubarrayLength(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
