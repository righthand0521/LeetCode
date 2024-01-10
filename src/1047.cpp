#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string removeDuplicates(string s) {
        string retVal;

        for (char c : s) {
            if (retVal.empty() == true) {
                retVal.push_back(c);
                continue;
            }

            if (retVal.back() == c) {
                retVal.pop_back();
            } else {
                retVal.push_back(c);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abbaca"}, {"azxxzy"}, {"bbaacaab"}, {"xrjjjjjrp"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abbaca"
     *  Output: "ca"
     *
     *  Input: s = "azxxzy"
     *  Output: "ay"
     *
     *  Input: s = "bbaacaab"
     *  Output: "cb"
     *
     *  Input: s = "xrjjjjjrp"
     *  Output: "xrjrp"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.removeDuplicates(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
