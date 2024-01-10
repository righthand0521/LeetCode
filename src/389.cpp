#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    char findTheDifference(string s, string t) {
        char retVal = 0;

        for (char c : s) {
            retVal ^= c;
        }

        for (char c : t) {
            retVal ^= c;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"abcd", "abcde"}, {"", "y"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcd", t = "abcde"
     *  Output: "e"
     *
     *  Input: s = "", t = "y"
     *  Output: "y"
     */

    Solution cSolution;
    char answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << ", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.findTheDifference(testData[i].s, testData[i].t);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
