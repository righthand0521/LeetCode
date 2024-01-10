#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string convertToTitle(int columnNumber) {
        string retVal;

        int multiple = 26;
        while (columnNumber > 0) {
            --columnNumber;
            int remainder = columnNumber % multiple;
            retVal += remainder + 'A';
            columnNumber /= multiple;
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int columnNumber;
    };
    vector<subject> testData{{1}, {28}, {701}, {2147483647}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: columnNumber = 1
     *  Output: "A"
     *
     *  Input: columnNumber = 28
     *  Output: "AB"
     *
     *  Input: columnNumber = 701
     *  Output: "ZY"
     *
     *  Input: columnNumber = 2147483647
     *  Output: "FXSHRXW"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: columnNumber = " << testData[i].columnNumber << "\n";

        answer = cSolution.convertToTitle(testData[i].columnNumber);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
