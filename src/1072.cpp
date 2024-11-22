#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int retVal = 0;

        unordered_map<string, int> patternFrequency;  // Map to store frequency of each pattern
        for (auto& currentRow : matrix) {
            string patternBuilder = "";

            // Convert row to pattern relative to its first element
            int currentRowSize = currentRow.size();
            for (int col = 0; col < currentRowSize; col++) {
                // 'T' if current element matches first element, 'F' otherwise
                if (currentRow[0] == currentRow[col]) {
                    patternBuilder += "T";
                } else {
                    patternBuilder += "F";
                }
            }

            // Convert pattern to string and update its frequency in map
            patternFrequency[patternBuilder]++;
        }

        // Find the pattern with maximum frequency
        for (auto& entry : patternFrequency) {
            retVal = max(entry.second, retVal);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{0, 1}, {1, 1}}}, {{{0, 1}, {1, 0}}}, {{{0, 0, 0}, {0, 0, 1}, {1, 1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[0,1],[1,1]]
     *  Output: 1
     *
     *  Input: matrix = [[0,1],[1,0]]
     *  Output: 2
     *
     *  Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].matrix[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxEqualRowsAfterFlips(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
