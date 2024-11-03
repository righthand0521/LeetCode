#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool rotateString(string s, string goal) {
        bool retVal = false;

        if (s.size() != goal.size()) {
            return retVal;
        }

        if ((s + s).find(goal) != string::npos) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string goal;
    };
    vector<subject> testData{{"abcde", "cdeab"}, {"abcde", "abced"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcde", goal = "cdeab"
     *  Output: true
     *
     *  Input: s = "abcde", goal = "abced"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", goal = \"" << testData[i].goal << "\"\n";

        answer = cSolution.rotateString(testData[i].s, testData[i].goal);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
