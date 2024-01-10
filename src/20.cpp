#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValid(string s) {
        bool retVal = false;

        // s consists of parentheses only '()[]{}'.
        unordered_map<char, char> parenthesesMap = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

        stack<char> stack;
        for (char c : s) {
            for (auto [key, value] : parenthesesMap) {
                if (c == key) {
                    stack.push(value);
                    break;
                }

                if (c == value) {
                    if (stack.empty() == true) {
                        return retVal;
                    }

                    if (c != stack.top()) {
                        return retVal;
                    }
                    stack.pop();
                }
            }
        }
        if (stack.empty() == true) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"()"}, {"()[]{}"}, {"(]"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "()"
     *  Output: true
     *
     *  Input: s = "()[]{}"
     *  Output: true
     *
     *  Input: s = "(]"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.isValid(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
