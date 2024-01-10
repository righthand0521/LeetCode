#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string methodStack(string s) {
        string retVal;

        for (char c : s) {
            if (c != '#') {
                retVal.push_back(c);
            } else if (retVal.empty() == false) {
                retVal.pop_back();
            }
        }

        return retVal;
    }
    bool methodTwoPointer(string s, string t) {
        bool retVal = false;

        int skipS = 0;
        int skipT = 0;

        int i = s.size() - 1;
        int j = t.size() - 1;
        while ((i >= 0) || (j >= 0)) {
            while (i >= 0) {
                if (s[i] == '#') {
                    skipS += 1;
                    i--;
                } else if (skipS > 0) {
                    skipS -= 1;
                    i--;
                } else {
                    break;
                }
            }

            while (j >= 0) {
                if (t[j] == '#') {
                    skipT += 1;
                    j--;
                } else if (skipT > 0) {
                    skipT -= 1;
                    j--;
                } else {
                    break;
                }
            }

            if ((i >= 0) && (j >= 0)) {
                if (s[i] != t[j]) {
                    return retVal;
                }
            } else if ((i >= 0) || (j >= 0)) {
                return retVal;
            }

            i--;
            j--;
        }
        retVal = true;

        return retVal;
    }
    bool backspaceCompare(string s, string t) {
        bool retVal = false;

#if (0)
        if (methodStack(s) == methodStack(t)) {
            retVal = true;
        }
#else
        retVal = methodTwoPointer(s, t);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"ab#c", "ad#c"}, {"ab##", "c#d#"}, {"a#c", "b"}, {"a##c", "#a#c"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ab#c", t = "ad#c"
     *  Output: true
     *
     *  Input: s = "ab##", t = "c#d#"
     *  Output: true
     *
     *  Input: s = "a#c", t = "b"
     *  Output: false
     *
     *  Input: s = "a##c", t = "#a#c"
     *  Output: true
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.backspaceCompare(testData[i].s, testData[i].t);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
