#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int retVal = 0;

        int arrSize = arr.size();
        unordered_map<int, int> numToIndex;
        for (int i = 0; i < arrSize; i++) {
            numToIndex[arr[i]] = i;
        }

        int matRowSize = mat.size();
        int matColSize = mat[0].size();
        retVal = numeric_limits<int>::max();
        for (int row = 0; row < matRowSize; row++) {
            int lastElementIndex = numeric_limits<int>::min();
            for (int col = 0; col < matColSize; col++) {
                int indexVal = numToIndex[mat[row][col]];
                lastElementIndex = max(lastElementIndex, indexVal);
            }
            retVal = min(retVal, lastElementIndex);
        }
        for (int col = 0; col < matColSize; col++) {
            int lastElementIndex = numeric_limits<int>::min();
            for (int row = 0; row < matRowSize; row++) {
                int indexVal = numToIndex[mat[row][col]];
                lastElementIndex = max(lastElementIndex, indexVal);
            }
            retVal = min(retVal, lastElementIndex);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        vector<vector<int>> mat;
    };
    vector<subject> testData{{{1, 3, 4, 2}, {{1, 4}, {2, 3}}},
                             {{2, 8, 7, 4, 1, 3, 5, 6, 9}, {{3, 2, 5}, {1, 4, 6}, {8, 7, 9}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
     *  Output: 2
     *
     *  Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], mat = [";
        for (long unsigned int j = 0; j < testData[i].mat.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].mat[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].mat[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.firstCompleteIndex(testData[i].arr, testData[i].mat);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
