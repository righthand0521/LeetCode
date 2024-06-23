#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSubarray(vector<int>& nums, int limit) {
        int retVal = 0;

        deque<int> maxDeque;
        deque<int> minDeque;
        int numsSize = nums.size();
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            // Maintain the maxDeque in decreasing order
            while ((maxDeque.empty() == false) && (maxDeque.back() < nums[right])) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(nums[right]);

            // Maintain the minDeque in increasing order
            while ((minDeque.empty() == false) && (minDeque.back() > nums[right])) {
                minDeque.pop_back();
            }
            minDeque.push_back(nums[right]);

            // Check if the current window exceeds the limit
            while (maxDeque.front() - minDeque.front() > limit) {
                // Remove the elements that are out of the current window
                if (maxDeque.front() == nums[left]) {
                    maxDeque.pop_front();
                }
                if (minDeque.front() == nums[left]) {
                    minDeque.pop_front();
                }

                ++left;
            }

            retVal = max(retVal, right - left + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int limit;
    };
    vector<subject> testData{{{8, 2, 4, 7}, 4}, {{10, 1, 2, 4, 7, 2}, 5}, {{4, 2, 2, 2, 4, 4, 2, 2}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [8,2,4,7], limit = 4
     *  Output: 2
     *
     *  Input: nums = [10,1,2,4,7,2], limit = 5
     *  Output: 4
     *
     *  Input: nums = [4,2,2,2,4,4,2,2], limit = 0
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], limit = " << testData[i].limit << "\n";

        answer = cSolution.longestSubarray(testData[i].nums, testData[i].limit);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
