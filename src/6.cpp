#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string convert(string s, int numRows) {
        string retVal;

        if (numRows == 1) {
            retVal = s;
            return retVal;
        }

        /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
         *
         *  n = 3: 2x(3-1) = 4
         *  +-------+-------+----+
         *  | 0 |   | 4 |   | 8  |
         *  | 1 | 3 | 5 | 7 | 9  | ...
         *  | 2 |   | 6 |   | 10 |
         *  +-------+-------+----+
         *
         *  n = 4: 2x(4-1) = 6
         *  +-----------+-------------+----+
         *  | 0 |   |   | 6 |    |    | 12 |
         *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
         *  | 2 | 4 |   | 8 | 10 |    | 14 |
         *  | 3 |   |   | 9 |    |    | 15 |
         *  +-----------+-------------+----+
         *
         *  n = 5: 2x(5-1) = 8
         *  +---------------+-------------------+----+
         *  | 0 |   |   |   |  8 |    |    |    | 16 |
         *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
         *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
         *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
         *  | 4 |   |   |   | 12 |    |    |    | 20 |
         *  +---------------+-------------------+----+
         */
        int len = s.length();
        int charsInSection = 2 * (numRows - 1);
        for (int currRow = 0; currRow < numRows; ++currRow) {
            int index = currRow;
            while (index < len) {
                retVal += s[index];

                // If currRow is not the first or last row then we have to add one more character of current section.
                if ((currRow != 0) && (currRow != numRows - 1)) {
                    int charsInBetween = charsInSection - 2 * currRow;
                    int secondIndex = index + charsInBetween;
                    if (secondIndex < len) {
                        retVal += s[secondIndex];
                    }
                }

                // Jump to same row's first character of next section.
                index += charsInSection;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int numRows;
    };
    vector<subject> testData{{"PAYPALISHIRING", 3}, {"PAYPALISHIRING", 4}, {"A", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "PAYPALISHIRING", numRows = 3
     *  Output: "PAHNAPLSIIGYIR"
     *
     *  Input: s = "PAYPALISHIRING", numRows = 4
     *  Output: "PINALSIGYAHRPI"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\", numRows = " << testData[i].numRows << "\n";

        answer = cSolution.convert(testData[i].s, testData[i].numRows);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
