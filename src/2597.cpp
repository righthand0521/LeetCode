#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int retVal = 1;

        // Calculate frequencies based on remainder
        map<int, map<int, int>> freqMap;
        for (int& num : nums) {
            freqMap[num % k][num]++;
        }

        // Iterate through each remainder group
        for (auto& fr : freqMap) {
            int prevNum = -k;
            int prev1 = 1;
            int prev2 = 1;
            int curr = 1;

            // Iterate through each number in the current remainder group
            for (auto& [num, freq] : fr.second) {
                // Count of subsets skipping the current number
                int skip = prev1;

                // Count of subsets including the current number
                // Check if the current number and the previous number form a beautiful pair
                int take;
                if (num - prevNum == k) {
                    take = ((1 << freq) - 1) * prev2;
                } else {
                    take = ((1 << freq) - 1) * prev1;
                }

                // Store the total count for the current number
                curr = skip + take;
                prev2 = prev1;
                prev1 = curr;
                prevNum = num;
            }
            retVal *= curr;
        }
        retVal = retVal - 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 4, 6}, 2}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,4,6], k = 2
     *  Output: 4
     *
     *  Input: nums = [1], k = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.beautifulSubsets(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
