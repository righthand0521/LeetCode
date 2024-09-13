#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> retVal;

        int arrSize = arr.size();
        int prefixSumSize = arrSize + 1;
        vector<int> prefixSum(prefixSumSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] ^ arr[i];
        }

        int queriesSize = queries.size();
        for (int i = 0; i < queriesSize; ++i) {
            retVal.emplace_back(prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{1, 3, 4, 8}, {{0, 1}, {1, 2}, {0, 3}, {3, 3}}},
                             {{4, 8, 2, 10}, {{2, 3}, {1, 3}, {0, 0}, {0, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
     *  Output: [2,7,14,8]
     *
     *  Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
     *  Output: [8,0,4,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
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

        answer = cSolution.xorQueries(testData[i].arr, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
