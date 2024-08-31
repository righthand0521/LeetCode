#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int backtrack(int n, int row, unordered_set<int>& columns, unordered_set<int>& diagonals1,
                  unordered_set<int>& diagonals2) {
        int retVal = 0;

        if (row == n) {
            retVal = 1;
            return retVal;
        }

        for (int i = 0; i < n; i++) {
            if (columns.find(i) != columns.end()) {
                continue;
            }

            int diagonal1 = row - i;
            if (diagonals1.find(diagonal1) != diagonals1.end()) {
                continue;
            }

            int diagonal2 = row + i;
            if (diagonals2.find(diagonal2) != diagonals2.end()) {
                continue;
            }

            columns.insert(i);
            diagonals1.insert(diagonal1);
            diagonals2.insert(diagonal2);
            retVal += backtrack(n, row + 1, columns, diagonals1, diagonals2);
            columns.erase(i);
            diagonals1.erase(diagonal1);
            diagonals2.erase(diagonal2);
        }

        return retVal;
    }
    int totalNQueens(int n) {
        int retVal = 0;

        unordered_set<int> columns;
        unordered_set<int> diagonals1;
        unordered_set<int> diagonals2;
        retVal = backtrack(n, 0, columns, diagonals1, diagonals2);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{4}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4
     *  Output: 2
     *
     *  Input: n = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.totalNQueens(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
