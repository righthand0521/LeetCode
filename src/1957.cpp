#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string makeFancyString(string s) {
        string retVal;

        for (char c : s) {
            int retValSize = retVal.size();
            if ((retValSize >= 2) && (retVal[retValSize - 1] == c) && (retVal[retValSize - 2] == c)) {
                continue;
            }
            retVal += c;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"leeetcode"}, {"aaabaaaa"}, {"aab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leeetcode"
     *  Output: "leetcode"
     *
     *  Input: s = "aaabaaaa"
     *  Output: "aabaa"
     *
     *  Input: s = "aab"
     *  Output: "aab"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.makeFancyString(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
