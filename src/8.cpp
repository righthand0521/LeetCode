#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int myAtoi(string s) {
        int retVal = 0;

        bool signStatus = false;
        bool numberStatus = false;
        bool isMinus = false;
        long sum = 0;
        for (auto c : s) {
            if ((c == '-') || (c == '+') || (c == ' ')) {
                if ((signStatus == true) || (numberStatus == true)) {
                    break;
                }

                if (c == '-') {
                    isMinus = true;
                }

                if (c != ' ') {
                    signStatus = true;
                }
            } else if ((c > '9') || (c < '0')) {
                break;
            } else {
                numberStatus = true;
                sum = 10 * sum + (c - '0');
                if (sum > numeric_limits<int>::max()) {
                    break;
                }
            }
        }

        if (isMinus == true) {
            sum = -(sum);
        }

        /* 5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
         *  then clamp the integer so that it remains in the range.
         *  Specifically, integers less than -2^31 should be clamped to -2^31,
         *  and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
         */
        if (sum > numeric_limits<int>::max()) {
            retVal = numeric_limits<int>::max();
        } else if (sum < numeric_limits<int>::min()) {
            retVal = numeric_limits<int>::min();
        } else {
            retVal = sum;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"42"},
                             {"   -42"},
                             {"4193 with words"},
                             {"words and 987"},
                             {"+-12"},
                             {"20000000000000000000"},
                             {"  0000000000012345678"},
                             {"00000-42a1234"},
                             {"  +  413"},
                             {"-91283472332"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "42"
     *  Output: 42
     *
     *  Input: s = "   -42"
     *  Output: -42
     *
     *  Input: s = "4193 with words"
     *  Output: 4193
     *
     *  Input: s = "words and 987"
     *  Output: 0
     *
     *  Input: s = "+-12"
     *  Output: 0
     *
     *  Input: s = "20000000000000000000"
     *  Output: 2147483647
     *
     *  Input: s = "  0000000000012345678"
     *  Output: 12345678
     *
     *  Input: s = "00000-42a1234"
     *  Output: 0
     *
     *  Input: s = "  +  413"
     *  Output: 0
     *
     *  Input: s = "-91283472332"
     *  Output: -2147483648
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.myAtoi(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
