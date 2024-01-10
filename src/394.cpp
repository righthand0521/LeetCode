#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    string decodeString(string s) {
        string retVal = "";

        stack<char> record;
        int repeatTimes;
        for (char c : s) {
            if (c != ']') {
                record.push(c);
                continue;
            }

            string currentString = "";
            while (record.top() != '[') {
                currentString = record.top() + currentString;
                record.pop();
            }
            record.pop();

            string number = "";
            while ((record.empty() == false) && (isdigit(record.top()))) {
                number = record.top() + number;
                record.pop();
            }

            repeatTimes = stoi(number);
            while (repeatTimes--) {
                for (char currentChar : currentString) {
                    record.push(currentChar);
                }
            }
        }

        while (record.empty() == false) {
            retVal = record.top() + retVal;
            record.pop();
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"3[a]2[bc]"}, {"3[a2[c]]"}, {"2[abc]3[cd]ef"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "3[a]2[bc]"
     *  Output: "aaabcbc"
     *
     *  Input: s = "3[a2[c]]"
     *  Output: "accaccacc"
     *
     *  Input: s = "2[abc]3[cd]ef"
     *  Output: "abcabccdcdcdef"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.decodeString(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
