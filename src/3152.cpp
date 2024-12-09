#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<bool> retVal;

        int numsSize = nums.size();
        vector<int> prefix(numsSize, 0);
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] % 2 == nums[i - 1] % 2) {
                prefix[i] = prefix[i - 1] + 1;  // new violative index found
            } else {
                prefix[i] = prefix[i - 1];
            }
        }

        for (auto& query : queries) {
            int start = query[0];
            int end = query[1];
            bool value = (prefix[end] - prefix[start] == 0);
            retVal.emplace_back(value);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{3, 4, 1, 2, 6}, {{0, 4}}}, {{4, 3, 1, 6}, {{0, 2}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,4,1,2,6], queries = [[0,4]]
     *  Output: [false]
     *
     *  Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
     *  Output: [false,true]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.isArraySpecial(testData[i].nums, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (answer[j] == true ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
