#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        vector<vector<int>> retVal;

        int rowSize = img.size();
        int colSize = img[0].size();

        retVal.resize(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                int sum = 0;
                int count = 0;
                for (int x = (i - 1); x <= (i + 1); ++x) {
                    for (int y = (j - 1); y <= (j + 1); ++y) {
                        if (((0 <= x) && (x < rowSize)) && ((0 <= y) && (y < colSize))) {
                            sum += img[x][y];
                            count += 1;
                        }
                    }
                }
                retVal[i][j] = sum / count;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> img;
    };
    vector<subject> testData{{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}}, {{{100, 200, 100}, {200, 50, 200}, {100, 200, 100}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: img = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: [[0,0,0],[0,0,0],[0,0,0]]
     *
     *  Input: img = [[100,200,100],[200,50,200],[100,200,100]]
     *  Output: [[137,141,137],[141,138,141],[137,141,137]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: img = [";
        for (long unsigned int j = 0; j < testData[i].img.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].img[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].img[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.imageSmoother(testData[i].img);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
