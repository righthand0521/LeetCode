#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxScore(string s) {
        int retVal = 0;

        int sSize = s.size();

        int ones = 0;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '1') {
                ones++;
            }
        }

        int zeros = 0;
        for (int i = 0; i < sSize - 1; ++i) {
            if (s[i] == '0') {
                zeros++;
            } else {
                ones--;
            }

            retVal = max(retVal, (zeros + ones));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"011101"}, {"00111"}, {"1111"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "011101"
     *  Output: 5
     *
     *  Input: s = "00111"
     *  Output: 5
     *
     *  Input: s = "1111"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxScore(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
