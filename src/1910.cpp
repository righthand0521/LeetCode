#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    bool checkMatch(stack<char>& stk, string& part, int partLength) {
        bool retVal = true;

        stack<char> temp = stk;
        for (int partIndex = partLength - 1; partIndex >= 0; partIndex--) {
            if (temp.top() != part[partIndex]) {
                retVal = false;
                break;
            }
            temp.pop();
        }

        return retVal;
    }

   public:
    string removeOccurrences(string s, string part) {
        string retVal = "";

        int sSize = s.size();
        int partSize = part.size();
        stack<char> stk;
        for (int index = 0; index < sSize; index++) {
            stk.push(s[index]);
            int stkSize = stk.size();
            if ((stkSize < partSize) || (checkMatch(stk, part, partSize) == false)) {
                continue;
            }

            for (int j = 0; j < partSize; j++) {
                stk.pop();
            }
        }

        while (stk.empty() == false) {
            retVal = stk.top() + retVal;
            stk.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string part;
    };
    vector<subject> testData{{"daabcbaabcbc", "abc"}, {"axxxxyyyyb", "xy"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "daabcbaabcbc", part = "abc"
     *  Output: "dab"
     *
     *  Input: s = "axxxxyyyyb", part = "xy"
     *  Output: "ab"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", part = \"" << testData[i].part << "\n";

        answer = cSolution.removeOccurrences(testData[i].s, testData[i].part);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
