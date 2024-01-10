#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string smallestSubsequence(string s) {
        string retVal;

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
        vector<int> appears(MAX_LETTERS, 0);
        for (char ch : s) {
            appears[ch - 'a']++;
        }

        vector<int> visit(MAX_LETTERS, 0);
        for (char ch : s) {
            int idx = ch - 'a';

            if (visit[idx] == 0) {
                while ((retVal.empty() == false) && (retVal.back() > ch)) {
                    if (appears[retVal.back() - 'a'] > 0) {
                        visit[retVal.back() - 'a'] = 0;
                        retVal.pop_back();
                    } else {
                        break;
                    }
                }
                visit[idx] = 1;
                retVal.push_back(ch);
            }

            appears[idx] -= 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"bcabc"}, {"cbacdcbc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "bcabc"
     *  Output: "abc"
     *
     *  Input: s = "cbacdcbc"
     *  Output: "acdb"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.smallestSubsequence(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
