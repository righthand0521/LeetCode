#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string makeGood(string s) {
        string retVal;

        for (char c : s) {
            if ((retVal.empty() == false) && (retVal.back() == (c ^ 32))) {
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
    vector<subject> testData{{"leEeetcode"}, {"abBAcC"}, {"s"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leEeetcode"
     *  Output: "leetcode"
     *
     *  Input: s = "abBAcC"
     *  Output: ""
     *
     *  Input: s = "s"
     *  Output: "s"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.makeGood(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
