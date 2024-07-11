#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string reverseParentheses(string s) {
        string retVal = "";

        vector<char> stack;
        for (char c : s) {
            if (c == ')') {
                vector<char> reverseStack;
                while (stack[stack.size() - 1] != '(') {
                    reverseStack.emplace_back(stack[stack.size() - 1]);
                    stack.erase(stack.end() - 1);
                }
                stack.erase(stack.end() - 1);
                stack.insert(stack.end(), reverseStack.begin(), reverseStack.end());
            } else {
                stack.emplace_back(c);
            }
        }
        for (char c : stack) {
            retVal += c;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"(abcd)"}, {"(u(love)i)"}, {"(ed(et(oc))el)"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "(abcd)"
     *  Output: "dcba"
     *
     *  Input: s = "(u(love)i)"
     *  Output: "iloveu"
     *
     *  Input: s = "(ed(et(oc))el)"
     *  Output: "leetcode"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.reverseParentheses(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
