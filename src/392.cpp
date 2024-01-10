#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isSubsequence(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize > tSize) {
            return retVal;
        }

        int sIdx = 0;
        int tIdx = 0;
        while ((sIdx < sSize) && (tIdx < tSize)) {
            if (s[sIdx] == t[tIdx]) {
                ++sIdx;
            }
            ++tIdx;
        }
        if (sIdx == sSize) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"abc", "ahbgdc"}, {"axc", "ahbgdc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abc", t = "ahbgdc"
     *  Output: true
     *
     *  Input: s = "axc", t = "ahbgdc"
     *  Output: false
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.isSubsequence(testData[i].s, testData[i].t);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
