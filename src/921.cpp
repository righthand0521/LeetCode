#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minAddToMakeValid(string s) {
        int retVal = 0;

        int openBrackets = 0;
        int minAddsRequired = 0;
        for (char c : s) {
            if (c == '(') {
                openBrackets++;
            } else {
                // If open bracket exists, match it with the closing one. If not, we need to add a open bracket.
                (openBrackets > 0) ? (openBrackets--) : (minAddsRequired++);
            }
        }

        // Add the remaining open brackets as closing brackets would be required.
        retVal = minAddsRequired + openBrackets;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"())"}, {"((("}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "())"
     *  Output: 1
     *
     *  Input: s = "((("
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minAddToMakeValid(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
