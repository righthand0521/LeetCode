#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSubmat(vector<vector<int>>& mat) {
        int retVal = 0;

        int matColSize = mat[0].size();

        vector<int> heights(matColSize, 0);
        for (const auto& row : mat) {
            for (int i = 0; i < matColSize; ++i) {
                heights[i] = (row[i] == 0) ? 0 : heights[i] + 1;
            }

            stack<vector<int>> monotonicStack;
            monotonicStack.push({-1, 0, -1});
            for (int i = 0; i < matColSize; ++i) {
                int h = heights[i];
                while (monotonicStack.top()[2] >= h) {
                    monotonicStack.pop();
                }

                auto& top = monotonicStack.top();
                int j = top[0];
                int prev = top[1];
                int cur = prev + (i - j) * h;
                monotonicStack.push({i, cur, h});

                retVal += cur;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
    };
    vector<subject> testData{{{{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}}, {{{0, 1, 1, 0}, {0, 1, 1, 1}, {1, 1, 1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
     *  Output: 13
     *
     *  Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
     *  Output: 24
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mat = [";
        for (long unsigned int j = 0; j < testData[i].mat.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].mat[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].mat[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.numSubmat(testData[i].mat);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
