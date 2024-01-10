#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        vector<pair<int, int>> sequence;
        for (int i = 0; i < numsSize; ++i) {
            sequence.emplace_back(i, nums[i]);
        }
        sort(sequence.begin(), sequence.end(), [&](auto x1, auto x2) {
            // descending order
            return x1.second > x2.second;
        });
        sort(sequence.begin(), sequence.begin() + k);

        for (int i = 0; i < k; ++i) {
            retVal.emplace_back(sequence[i].second);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 1, 3, 3}, 2}, {{-1, -2, 3, 4}, 3}, {{3, 4, 3, 3}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,3,3], k = 2
     *  Output: [3,3]
     *
     *  Input: nums = [-1,-2,3,4], k = 3
     *  Output: [-1,3,4]
     *
     *  Input: nums = [3,4,3,3], k = 2
     *  Output: [3,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxSubsequence(testData[i].nums, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
