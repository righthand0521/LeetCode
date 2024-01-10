#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define BINARY_SEARCH (1)
#define SORTING (1)
   public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        vector<int> retVal;

        sort(nums.begin(), nums.end());
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int numsSize = nums.size();
        vector<int> prefixSum(numsSize, 0);
        prefixSum[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (auto query : queries) {
            auto iterator = upper_bound(prefixSum.begin(), prefixSum.end(), query);
            retVal.emplace_back(iterator - prefixSum.begin());
        }
#elif (SORTING)
        cout << "SORTING\n";

        for (int query : queries) {
            int count = 0;
            for (int num : nums) {
                query -= num;
                if (query < 0) {
                    break;
                }
                ++count;
            }
            retVal.emplace_back(count);
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<int> queries;
    };
    vector<subject> testData{{{4, 5, 2, 1}, {3, 10, 21}}, {{2, 3, 4, 5}, {1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,5,2,1], queries = [3,10,21]
     *  Output: [2,3,4]
     *
     *  Input: nums = [2,3,4,5], queries = [1]
     *  Output: [0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].queries[j];
        }
        cout << "]\n";

        answer = cSolution.answerQueries(testData[i].nums, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
