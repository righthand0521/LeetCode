#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long retVal = 0;

        int numsSize = nums.size();
        long long total = 0;
        int head = 0;
        for (int tail = 0; tail < numsSize; ++tail) {
            total += nums[tail];
            while ((head <= tail) && (total * (tail - head + 1) >= k)) {
                total -= nums[head];
                ++head;
            }
            retVal += (tail - head + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 1, 4, 3, 5}, 10}, {{1, 1, 1}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,4,3,5], k = 10
     *  Output: 6
     *
     *  Input: nums = [1,1,1], k = 5
     *  Output: 5
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].k << "\n";

        answer = cSolution.countSubarrays(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
