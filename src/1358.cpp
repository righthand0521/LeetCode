#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfSubstrings(string s) {
        int retVal = 0;

        vector<int> lastPos = {-1, -1, -1};  // Track last position of a, b, c
        int sSize = s.length();
        for (int pos = 0; pos < sSize; pos++) {
            // Update last position of current character
            lastPos[s[pos] - 'a'] = pos;

            // Add count of valid substrings ending at current position
            // If any character is missing, min will be -1
            // Else min gives leftmost required character position
            retVal += 1 + min({lastPos[0], lastPos[1], lastPos[2]});
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abcabc"}, {"aaacb"}, {"abc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcabc"
     *  Output: 10
     *
     *  Input: s = "aaacb"
     *  Output: 3
     *
     *  Input: s = "abc"
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numberOfSubstrings(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
