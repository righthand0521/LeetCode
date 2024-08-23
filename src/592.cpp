#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    string fractionAddition(string expression) {
        string retVal = "0/1";

        int expressionSize = expression.size();

        long long numerator = 0;
        long long denominator = 1;
        int index = 0;
        while (index < expressionSize) {
            long long sign = 1;
            long long x = 0;
            if ((expression[index] == '-') || (expression[index] == '+')) {
                sign = expression[index] == '-' ? -1 : 1;
                index++;
            }
            while ((index < expressionSize) && (isdigit(expression[index]))) {
                x = x * 10 + expression[index] - '0';
                index++;
            }
            x = sign * x;
            index++;

            long long y = 0;
            while ((index < expressionSize) && (isdigit(expression[index]))) {
                y = y * 10 + expression[index] - '0';
                index++;
            }

            numerator = numerator * y + x * denominator;
            denominator *= y;
        }

        if (numerator != 0) {
            long long greatestCommonDivisor = gcd(abs(numerator), denominator);
            retVal = to_string(numerator / greatestCommonDivisor);
            retVal += "/";
            retVal += to_string(denominator / greatestCommonDivisor);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string expression;
    };
    vector<subject> testData{{"-1/2+1/2"}, {"-1/2+1/2+1/3"}, {"1/3-1/2"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: expression = "-1/2+1/2"
     *  Output: "0/1"
     *
     *  Input: expression = "-1/2+1/2+1/3"
     *  Output: "1/3"
     *
     *  Input: expression = "1/3-1/2"
     *  Output: "-1/6"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: expression = \"" << testData[i].expression << "\"\n";

        answer = cSolution.fractionAddition(testData[i].expression);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
