#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestValidParentheses(string s) {
        int retVal = 0;

        stack<int> stack;
        stack.push(-1);

        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            if (s[i] == '(') {
                stack.push(i);
                continue;
            }

            stack.pop();
            if (stack.empty()) {
                stack.push(i);
            } else {
                retVal = max(retVal, i - stack.top());
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"(()"}, {")()())"}, {""}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "(()"
     *  Output: 2
     *
     *  Input: s = ")()())"
     *  Output: 4
     *
     *  Input: s = ""
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.longestValidParentheses(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
