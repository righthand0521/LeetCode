#include <ctype.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool areNumbersAscending(string s) {
        bool retVal = false;

        int checkNum = -1;
        int num = 0;
        bool continueNum = false;
        for (auto c : s) {
            if (isdigit(c)) {
                num = 10 * num + (c - '0');
                continueNum = true;
                continue;
            }

            if (continueNum == true) {
                if (num <= checkNum) {
                    return retVal;
                }
                checkNum = num;
            }

            num = 0;
            continueNum = false;
            continue;
        }
        if (num != 0) {
            if (num <= checkNum) {
                return retVal;
            }
            checkNum = num;
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"1 box has 3 blue 4 red 6 green and 12 yellow marbles"},
                             {"hello world 5 x 5"},
                             {"sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
     *  Output: true
     *
     *  Input: s = "hello world 5 x 5"
     *  Output: false
     *
     *  Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.areNumbersAscending(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
