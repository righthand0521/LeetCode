#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<int> retVal;

        vector<pair<int, int>> value;

        int matSize = mat.size();
        for (int row = 0; row < matSize; ++row) {
            int soldiers = 0;
            int matColSize = mat[row].size();
            for (int col = 0; col < matColSize; ++col) {
                if (mat[row][col] == 0) {
                    break;
                }
                soldiers++;
            }
            value.emplace_back(soldiers, row);
        }

        priority_queue heap(greater<pair<int, int>>(), move(value));
        for (int i = 0; i < k; ++i) {
            retVal.push_back(heap.top().second);
            heap.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
        int k;
    };
    vector<subject> testData{{{{1, 1, 0, 0, 0}, {1, 1, 1, 1, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 1, 1}}, 3},
                             {{{1, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat =Input: mat = [[1,1,0,0,0], [1,1,1,1,0], [1,0,0,0,0], [1,1,0,0,0], [1,1,1,1,1]], k = 3
     *  Output: [2,0,3]
     *
     *  Input: mat = [[1,0,0,0], [1,1,1,1], [1,0,0,0], [1,0,0,0]], k = 2
     *  Output: [0,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mat = [";
        for (long unsigned int j = 0; j < testData[i].mat.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].mat[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].mat[j][k];
            }
            cout << "]";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kWeakestRows(testData[i].mat, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
