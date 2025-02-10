#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string clearDigits(string s) {
        string retVal;

        for (char c : s) {
            if (isdigit(c) != 0) {
                retVal.pop_back();
            } else {
                retVal += c;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abc"}, {"cb34"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abc"
     *  Output: "abc"
     *
     *  Input: s = "cb34"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.clearDigits(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
