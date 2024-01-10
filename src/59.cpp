#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> retVal(n, vector<int>(n));

        /*
         *  (top,left)                              (top,right)
         *      +---------------------------------------+
         *      | 01(111) | 02(112) | 03(113) | 04(114) |
         *      | 12(142) | 13(211) | 14(212) | 05(121) |
         *      | 11(141) | 16(231) | 15(221) | 06(122) |
         *      | 10(133) | 09(132) | 08(131) | 07(123) |
         *      +---------------------------------------+
         * (down,left)                             (down,right)
         */
        int left = 0;
        int right = n - 1;
        int top = 0;
        int down = n - 1;
        int num = 1;
        while ((left <= right) && (top <= down)) {
            for (int col = left; col < right + 1; ++col) {
                retVal[top][col] = num;
                ++num;
            }

            for (int row = top + 1; row < down + 1; ++row) {
                retVal[row][right] = num;
                ++num;
            }

            if ((left < right) && (top < down)) {
                for (int col = right - 1; col > left; --col) {
                    retVal[down][col] = num;
                    ++num;
                }

                for (int row = down; row > top; --row) {
                    retVal[row][left] = num;
                    ++num;
                }
            }

            ++left;
            --right;
            ++top;
            --down;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: [[1,2,3],[8,9,4],[7,6,5]]
     *
     *  Input: n = 1
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.generateMatrix(testData[i].n);
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
