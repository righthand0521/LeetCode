#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string removeStars(string s) {
        string retVal = "";

        for (char c : s) {
            if (c != '*') {
                retVal.push_back(c);
            } else {
                retVal.pop_back();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"leet**cod*e"}, {"erase*****"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leet**cod*e"
     *  Output: "lecoe"
     *
     *  Input: s = "erase*****"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.removeStars(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
