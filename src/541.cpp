#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string reverseStr(string s, int k) {
        string retVal = s;

        int retValSize = retVal.size();
        for (int i = 0; i < retValSize; i += 2 * k) {
            reverse(retVal.begin() + i, retVal.begin() + min(i + k, retValSize));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"abcdefg", 2}, {"abcd", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcdefg", k = 2
     *  Output: "bacdfeg"
     *
     *  Input: s = "abcd", k = 2
     *  Output: "bacd"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.reverseStr(testData[i].s, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
