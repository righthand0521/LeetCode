#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool doesAliceWin(string s) {
        bool retVal = false;

        for (char c : s) {
            if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"leetcoder"}, {"bbcd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leetcoder"
     *  Output: true
     *
     *  Input: s = "bbcd"
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.doesAliceWin(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
