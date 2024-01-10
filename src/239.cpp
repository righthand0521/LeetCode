#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> retVal;

        deque<int> doubleEndedQueue;

        for (int i = 0; i < k; ++i) {
            while ((doubleEndedQueue.empty() == false) && (nums[i] >= nums[doubleEndedQueue.back()])) {
                doubleEndedQueue.pop_back();
            }
            doubleEndedQueue.push_back(i);
        }
        retVal.emplace_back(nums[doubleEndedQueue.front()]);

        int numsSize = nums.size();
        for (int i = k; i < numsSize; ++i) {
            while ((doubleEndedQueue.empty() == false) && (nums[i] >= nums[doubleEndedQueue.back()])) {
                doubleEndedQueue.pop_back();
            }
            doubleEndedQueue.push_back(i);

            while (doubleEndedQueue.front() <= i - k) {
                doubleEndedQueue.pop_front();
            }
            retVal.emplace_back(nums[doubleEndedQueue.front()]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 3, -1, -3, 5, 3, 6, 7}, 3}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
     *  Output: [3,3,5,5,6,7]
     *
     *  Input: nums = [1], k = 1
     *  Output: [1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxSlidingWindow(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
