#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int scoreOfString(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 1; i < sSize; ++i) {
            retVal += abs(s[i - 1] - s[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"hello"}, {"zaz"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "hello"
     *  Output: 13
     *
     *  Input: s = "zaz"
     *  Output: 50
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.scoreOfString(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
