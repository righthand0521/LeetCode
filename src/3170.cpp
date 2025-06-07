#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    const int letters = 26;  // s consists only of lowercase English letters and '*'.

   public:
    string clearStars(string s) {
        string retVal = "";

        vector<stack<int>> lettersStack(letters);
        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                lettersStack[s[i] - 'a'].push(i);
                continue;
            }
            for (int j = 0; j < letters; j++) {
                if (lettersStack[j].empty() == false) {
                    s[lettersStack[j].top()] = '*';
                    lettersStack[j].pop();
                    break;
                }
            }
        }

        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                retVal += s[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aaba*"}, {"abc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaba*"
     *  Output: "aab"
     *
     *  Input: s = "abc"
     *  Output: "abc"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.clearStars(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
