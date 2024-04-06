#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string minRemoveToMakeValid(string s) {
        string retVal;

        int sSize = s.size();

        vector<int> parenthesesRight;
        vector<int> parenthesesStack;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '(') {
                parenthesesStack.push_back(i);
            } else if (s[i] == ')') {
                int parenthesesStackSize = parenthesesStack.size();
                if (parenthesesStackSize == 0) {
                    parenthesesRight.push_back(i);
                } else {
                    parenthesesStack.pop_back();
                }
            }
        }
        parenthesesStack.insert(parenthesesStack.end(), parenthesesRight.begin(), parenthesesRight.end());

        for (int i = 0; i < sSize; ++i) {
            if (find(parenthesesStack.begin(), parenthesesStack.end(), i) != parenthesesStack.end()) {
                continue;
            }
            retVal.push_back(s[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"lee(t(c)o)de)"}, {"a)b(c)d"}, {"))(("}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "lee(t(c)o)de)"
     *  Output: "lee(t(c)o)de"
     *
     *  Input: s = "a)b(c)d"
     *  Output: "ab(c)d"
     *
     *  Input: s = "))(("
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.minRemoveToMakeValid(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
