#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countHomogenous(string s) {
        int retVal = 1;  // 1 <= s.length <= 10^5

        int sSize = s.size();
        int homogenous = 1;
        for (int i = 1; i < sSize; ++i) {
            if (s[i - 1] == s[i]) {
                homogenous += 1;
            } else {
                homogenous = 1;
            }

            retVal += homogenous;
            retVal %= MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abbcccaa"}, {"xy"}, {"zzzzz"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abbcccaa"
     *  Output: 13
     *
     *  Input: s = "xy"
     *  Output: 2
     *
     *  Input: s = "zzzzz"
     *  Output: 15
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\n";

        answer = cSolution.countHomogenous(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
