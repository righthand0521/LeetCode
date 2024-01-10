#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkString(string s) {
        bool retVal = true;

        bool isChanged = false;
        for (auto c : s) {
            if (c == 'a') {
                if (isChanged == true) {
                    retVal = false;
                    return retVal;
                }
                continue;
            }

            isChanged = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aaabbb"}, {"abab"}, {"bbb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaabbb"
     *  Output: true
     *
     *  Input: s = "abab"
     *  Output: false
     *
     *  Input: s = "bbb"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.checkString(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
