#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string reverseWords(string s) {
        string retVal = "";

        int sSize = s.size();
        string splitStr = "";
        for (int i = 0; i <= sSize; ++i) {
            if ((s[i] != ' ') && (s[i] != '\0')) {
                splitStr.push_back(s[i]);
                continue;
            }

            if (splitStr.empty() == true) {
                continue;
            }
            retVal = splitStr + " " + retVal;

            splitStr = "";
        }
        retVal.pop_back();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"the sky is blue"}, {"  hello world  "}, {"a good   example"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "the sky is blue"
     *  Output: "blue is sky the"
     *
     *  Input: s = "  hello world  "
     *  Output: "world hello"
     *
     *  Input: s = "a good   example"
     *  Output: "example good a"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.reverseWords(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
