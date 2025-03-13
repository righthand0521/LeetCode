#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int retVal = 0;

        int numsSize = nums.size();
        int queriesSize = queries.size();

        int sum = 0;
        vector<int> differenceArray(numsSize + 1);
        for (int index = 0; index < numsSize; index++) {
            // Iterate through queries while current index of nums cannot equal zero
            while (sum + differenceArray[index] < nums[index]) {
                retVal++;
                // Zero array isn't formed after all queries are processed
                if (retVal > queriesSize) {
                    retVal = -1;
                    return retVal;
                }

                // Process start and end of range
                int left = queries[retVal - 1][0];
                int right = queries[retVal - 1][1];
                int val = queries[retVal - 1][2];
                if (right >= index) {
                    differenceArray[max(left, index)] += val;
                    differenceArray[right + 1] -= val;
                }
            }

            sum += differenceArray[index];  // Update prefix sum at current index
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{2, 0, 2}, {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}}}, {{4, 3, 2, 1}, {{1, 3, 2}, {0, 2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
     *  Output: 2
     *
     *  Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
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

        answer = cSolution.minZeroArray(testData[i].nums, testData[i].queries);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
