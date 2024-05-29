#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSteps(string s) {
        int retVal = 0;

        int sSize = s.size();
        int operations = 0;
        int carry = 0;
        for (int i = sSize - 1; i > 0; i--) {
            if (((s[i] - '0') + carry) % 2) {
                operations += 2;
                carry = 1;
            } else {
                operations++;
            }
        }
        retVal = operations + carry;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"1101"}, {"10"}, {"1"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1101"
     *  Output: 6
     *
     *  Input: s = "10"
     *  Output: 1
     *
     *  Input: s = "1"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numSteps(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
