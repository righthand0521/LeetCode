#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int countPartitions(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<long long> dp(numsSize + 1);
        dp[0] = 1;
        vector<long long> prefix(numsSize + 1);
        prefix[0] = 1;
        deque<int> minQueue;
        deque<int> maxQueue;

        for (int i = 0, j = 0; i < numsSize; i++) {
            // maintain the maximum value queue
            while ((maxQueue.empty() == false) && (nums[maxQueue.back()] <= nums[i])) {
                maxQueue.pop_back();
            }
            maxQueue.push_back(i);

            // maintain the minimum value queue
            while ((minQueue.empty() == false) && (nums[minQueue.back()] >= nums[i])) {
                minQueue.pop_back();
            }
            minQueue.push_back(i);

            // adjust window
            while ((maxQueue.empty() == false) && (minQueue.empty() == false) &&
                   (nums[maxQueue.front()] - nums[minQueue.front()] > k)) {
                if (maxQueue.front() == j) {
                    maxQueue.pop_front();
                }
                if (minQueue.front() == j) {
                    minQueue.pop_front();
                }
                j++;
            }

            dp[i + 1] = (prefix[i] - (j > 0 ? prefix[j - 1] : 0) + MODULO) % MODULO;
            prefix[i + 1] = (prefix[i] + dp[i + 1]) % MODULO;
        }
        retVal = dp[numsSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{9, 4, 1, 3, 7}, 4}, {{3, 3, 4}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [9,4,1,3,7], k = 4
     *  Output: 6
     *
     *  Input: nums = [3,3,4], k = 0
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

        answer = cSolution.countPartitions(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
