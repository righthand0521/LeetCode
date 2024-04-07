#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int calculate(string s) {
        int retVal = 0;

        vector<int> stack;
        int sign = 1;
        int num = 0;
        for (auto ch : s) {
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if ((ch == '+') || (ch == '-')) {
                retVal += (sign * num);
                num = 0;
                sign = (ch == '+') ? 1 : -1;
            } else if (ch == '(') {
                stack.emplace_back(retVal);
                stack.emplace_back(sign);
                retVal = 0;
                sign = 1;
            } else if (ch == ')') {
                retVal += (sign * num);
                num = 0;
                retVal *= stack.back();
                stack.pop_back();
                retVal += stack.back();
                stack.pop_back();
            }
        }
        retVal += (sign * num);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"1 + 1"}, {" 2-1 + 2 "}, {"(1+(4+5+2)-3)+(6+8)"}, {"1-(     -2)"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1 + 1"
     *  Output: 2
     *
     *  Input: s = " 2-1 + 2 "
     *  Output: 3
     *
     *  Input: s = "(1+(4+5+2)-3)+(6+8)"
     *  Output: 23
     *
     *  Input: s = "1-(     -2)"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.calculate(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
