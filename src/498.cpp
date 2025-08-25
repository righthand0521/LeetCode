#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> retVal;

        if ((mat.empty()) || (mat[0].empty())) {
            return retVal;
        }

        int matSize = mat.size();
        int matColSize = mat[0].size();
        int row = 0;
        int column = 0;
        int direction = 1;
        while ((row < matSize) && (column < matColSize)) {
            retVal.emplace_back(mat[row][column]);

            // Move along in the current diagonal depending upon the current direction.[i, j]->[i - 1, j + 1]
            // if going up and [ i, j ]->[i + 1][j - 1] if going down.
            int nextRow = row + ((direction == 1) ? (-1) : (1));
            int nextColumn = column + ((direction == 1) ? (1) : (-1));

            // Checking if the next element in the diagonal is within the bounds of the mat or not.
            // If it's not within the bounds, we have to find the next head.
            if ((nextRow < 0) || (nextRow == matSize) || (nextColumn < 0) || (nextColumn == matColSize)) {
                // If the current diagonal was going in the upwards direction.
                if (direction) {
                    // For an upwards going diagonal having[i, j] as its tail
                    // If[i, j + 1] is within bounds, then it becomes the next head.Otherwise, the element directly
                    // below i.e.the element[i + 1, j] becomes the next head
                    row += (column == matColSize - 1);
                    column += (column < matColSize - 1);
                } else {
                    // For a downwards going diagonal having[i, j] as its tail
                    // if [i + 1, j] is within bounds, then it becomes the next head.Otherwise, the element directly
                    // below i.e.the element[i, j + 1] becomes the next head
                    column += (row == matSize - 1);
                    row += (row < matSize - 1);
                }

                // Flip the direction
                direction = 1 - direction;
            } else {
                row = nextRow;
                column = nextColumn;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}}, {{{1, 2}, {3, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,2,4,7,5,3,6,8,9]
     *
     *  Input: mat = [[1,2],[3,4]]
     *  Output: [1,2,3,4]
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
        cout << "]\n";

        answer = cSolution.findDiagonalOrder(testData[i].mat);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
