#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string finalString(string s) {
        string retVal = "";

        for (char c : s) {
            if (c == 'i') {
                reverse(retVal.begin(), retVal.end());
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
    vector<subject> testData{{"string"}, {"poiinter"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "string"
     *  Output: "rtsng"
     *
     *  Input: s = "poiinter"
     *  Output: "ponter"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.finalString(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
