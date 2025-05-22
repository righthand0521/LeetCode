#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int retVal = -1;

        int queriesSize = queries.size();
        sort(queries.begin(), queries.end(), [](const vector<int>& a, const vector<int>& b) {
            // ascending order
            return a[0] < b[0];
        });

        priority_queue<int> heap;

        int numsSize = nums.size();
        vector<int> deltaArray(numsSize + 1, 0);
        int operations = 0;
        for (int i = 0, j = 0; i < numsSize; ++i) {
            operations += deltaArray[i];

            while ((j < queriesSize) && (queries[j][0] == i)) {
                heap.push(queries[j][1]);
                ++j;
            }

            while ((operations < nums[i]) && (heap.empty() == false) && (heap.top() >= i)) {
                operations += 1;
                deltaArray[heap.top() + 1] -= 1;
                heap.pop();
            }

            if (operations < nums[i]) {
                return retVal;
            }
        }
        retVal = heap.size();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{2, 0, 2}, {{0, 2}, {0, 2}, {1, 1}}},
                             {{1, 1, 1, 1}, {{1, 3}, {0, 2}, {1, 3}, {1, 2}}},
                             {{1, 2, 3, 4}, {{0, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
     *  Output: 1
     *
     *  Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4], queries = [[0,3]]
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

        answer = cSolution.maxRemoval(testData[i].nums, testData[i].queries);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
