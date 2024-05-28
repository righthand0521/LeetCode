#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestNiceSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int niceCheck = 0;
        int head = 0;
        int tail = 0;
        while (tail < numsSize) {
            while ((niceCheck & nums[tail]) != 0) {
                niceCheck ^= nums[head];
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            niceCheck |= nums[tail];
            tail++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 8, 48, 10}}, {{3, 1, 5, 11, 13}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,8,48,10]
     *  Output: 3
     *
     *  Input: nums = [3,1,5,11,13]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestNiceSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
