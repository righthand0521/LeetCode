#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkValidString(string s) {
        bool retVal = false;

        int sSize = s.size();
        int leftParenthesis = 0;
        int rightParenthesis = 0;
        for (int left = 0; left < sSize; ++left) {
            if ((s[left] == '(') || (s[left] == '*')) {
                leftParenthesis++;
            } else if (s[left] == ')') {
                leftParenthesis--;
            }

            int right = sSize - 1 - left;
            if ((s[right] == ')') || (s[right] == '*')) {
                rightParenthesis++;
            } else if (s[right] == '(') {
                rightParenthesis--;
            }

            if ((leftParenthesis < 0) || (rightParenthesis < 0)) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"()"}, {"(*)"}, {"(*))"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "()"
     *  Output: true
     *
     *  Input: s = "(*)"
     *  Output: true
     *
     *  Input: s = "(*))"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.checkValidString(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
