#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int subarraySum(vector<int>& prefixSumList, int target) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        hashTable[0] = 1;

        int prefixSum = 0;
        for (int value : prefixSumList) {
            prefixSum += value;
            if (hashTable.find(prefixSum - target) != hashTable.end()) {
                retVal += hashTable[prefixSum - target];
            }
            hashTable[prefixSum]++;
        }

        return retVal;
    }
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int retVal = 0;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        for (int row = 0; row < rowSize; ++row) {
            vector<int> prefixSum(colSize, 0);
            for (int x = row; x < rowSize; ++x) {
                for (int y = 0; y < colSize; ++y) {
                    prefixSum[y] += matrix[x][y];
                }
                retVal += subarraySum(prefixSum, target);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
        int target;
    };
    vector<subject> testData{{{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, 0}, {{{1, -1}, {-1, 1}}, 0}, {{{904}}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
     *  Output: 4
     *
     *  Input: matrix = [[1,-1],[-1,1]], target = 0
     *  Output: 5
     *
     *  Input: matrix = [[904]], target = 0
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.numSubmatrixSumTarget(testData[i].matrix, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
