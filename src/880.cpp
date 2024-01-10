#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string decodeAtIndex(string s, int k) {
        string retVal = "";

        int sSize = s.size();

        long size = 0;
        for (int i = 0; i < sSize; ++i) {
            if (isdigit(s[i]) != 0) {
                size *= (s[i] - '0');
            } else {
                size++;
            }
        }

        for (int i = sSize - 1; i >= 0; --i) {
            k %= size;
            if ((k == 0) && (isalpha(s[i]) != 0)) {
                retVal = s[i];
                break;
            }

            if (isdigit(s[i]) != 0) {
                size /= (s[i] - '0');
            } else {
                size--;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"leet2code3", 10}, {"ha22", 5}, {"a2345678999999999999999", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leet2code3", k = 10
     *  Output: "o"
     *
     *  Input: s = "ha22", k = 5
     *  Output: "h"
     *
     *  Input: s = "a2345678999999999999999", k = 1
     *  Output: "a"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.decodeAtIndex(testData[i].s, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
