#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool parseBoolExpr(string expression) {
        bool retVal = false;

        stack<char> st;
        for (char c : expression) {
            if (c == ',' || c == '(') {
                continue;
            } else if ((c == 't') || (c == 'f') || (c == '!') || (c == '&') || (c == '|')) {
                st.push(c);
            } else if (c == ')') {
                bool hasTrue = false;
                bool hasFalse = false;
                while ((st.top() != '!') && (st.top() != '&') && (st.top() != '|')) {
                    char topValue = st.top();
                    st.pop();
                    if (topValue == 't') {
                        hasTrue = true;
                    } else if (topValue == 'f') {
                        hasFalse = true;
                    }
                }

                char op = st.top();
                st.pop();
                if (op == '!') {
                    st.push((hasTrue == true) ? 'f' : 't');
                } else if (op == '&') {
                    st.push((hasFalse == true) ? 'f' : 't');
                } else {
                    st.push((hasTrue == true) ? 't' : 'f');
                }
            }
        }
        if (st.top() == 't') {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string expression;
    };
    vector<subject> testData{{"&(|(f))"}, {"|(f,f,f,t)"}, {"!(&(f,t))"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: expression = "&(|(f))"
     *  Output: false
     *
     *  Input: expression = "|(f,f,f,t)"
     *  Output: true
     *
     *  Input: expression = "!(&(f,t))"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: expression = \"" << testData[i].expression << "\"\n";

        answer = cSolution.parseBoolExpr(testData[i].expression);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
