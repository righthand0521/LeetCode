#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        int retVal = 0;

        stack<int> stack;
        for (string token : tokens) {
            int value = 0;

            // tokens[i] is either an operator: "+", "-", "*", or "/"
            if ((token == "+") || (token == "-") || (token == "*") || (token == "/")) {
                value = stack.top();
                stack.pop();
                if (token == "+") {
                    value = stack.top() + value;
                } else if (token == "-") {
                    value = stack.top() - value;
                } else if (token == "*") {
                    value = stack.top() * value;
                } else if (token == "/") {
                    value = stack.top() / value;
                }
                stack.pop();
            } else {
                value = stoi(token);
            }

            stack.push(value);
        }
        retVal = stack.top();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> tokens;
    };
    vector<subject> testData{{{"2", "1", "+", "3", "*"}},
                             {{"4", "13", "5", "/", "+"}},
                             {{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tokens = ["2","1","+","3","*"]
     *  Output: 9
     *
     *  Input: tokens = ["4","13","5","/","+"]
     *  Output: 6
     *
     *  Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
     *  Output: 22
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tokens = [";
        for (long unsigned int j = 0; j < testData[i].tokens.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].tokens[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.evalRPN(testData[i].tokens);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
