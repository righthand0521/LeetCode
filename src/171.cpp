#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int titleToNumber(string columnTitle) {
        int retVal = 0;

        int multiple = 26;
        int columnTitleSize = columnTitle.size();
        for (int i = 0; i < columnTitleSize; ++i) {
            retVal *= multiple;
            retVal += columnTitle[i] - 'A' + 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string columnTitle;
    };
    vector<subject> testData{{"A"}, {"AB"}, {"ZY"}, {"FXSHRXW"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: columnTitle = "A"
     *  Output: 1
     *
     *  Input: columnTitle = "AB"
     *  Output: 28
     *
     *  Input: columnTitle = "ZY"
     *  Output: 701
     *
     *  Input: columnTitle = "FXSHRXW"
     *  Output: 2147483647
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: columnTitle = \"" << testData[i].columnTitle << "\"\n";

        answer = cSolution.titleToNumber(testData[i].columnTitle);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
