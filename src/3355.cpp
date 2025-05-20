#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        bool retVal = true;

        int numsSize = nums.size();

        vector<int> deltaArray(numsSize + 1, 0);
        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];
            deltaArray[left] += 1;
            deltaArray[right + 1] -= 1;
        }

        vector<int> operationCounts;
        int currentOperations = 0;
        for (int delta : deltaArray) {
            currentOperations += delta;
            operationCounts.push_back(currentOperations);
        }

        for (int i = 0; i < numsSize; ++i) {
            if (operationCounts[i] < nums[i]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{1, 0, 1}, {{0, 2}}}, {{4, 3, 2, 1}, {{1, 3}, {0, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,0,1], queries = [[0,2]]
     *  Output: true
     *
     *  Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
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

        answer = cSolution.isZeroArray(testData[i].nums, testData[i].queries);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
