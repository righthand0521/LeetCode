#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canBeValid(string s, string locked) {
        bool retVal = false;

        int sSize = s.size();
        if (sSize % 2 == 1) {
            return retVal;
        }

        stack<int> openBrackets;
        stack<int> unlocked;
        for (int i = 0; i < sSize; i++) {
            if (locked[i] == '0') {
                unlocked.push(i);
            } else if (s[i] == '(') {
                openBrackets.push(i);
            } else if (s[i] == ')') {
                if (openBrackets.empty() == false) {
                    openBrackets.pop();
                } else if (unlocked.empty() == false) {
                    unlocked.pop();
                } else {
                    return retVal;
                }
            }
        }

        while ((openBrackets.empty() == false) && (unlocked.empty() == false) &&
               (openBrackets.top() < unlocked.top())) {
            openBrackets.pop();
            unlocked.pop();
        }
        if (openBrackets.empty() == true) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string locked;
    };
    vector<subject> testData{{"))()))", "010100"}, {"()()", "0000"}, {")", "0"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "))()))", locked = "010100"
     *  Output: true
     *
     *  Input: s = "()()", locked = "0000"
     *  Output: true
     *
     *  Input: s = ")", locked = "0"
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", locked = \"" << testData[i].locked << "\"\n";

        answer = cSolution.canBeValid(testData[i].s, testData[i].locked);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
