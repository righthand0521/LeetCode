#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string minWindow(string s, string t) {
        string retVal;

        int sSize = s.size();
        int tSize = t.size();

        unordered_map<char, int> hashSet;
        for (char c : t) {
            ++hashSet[c];
        }

        /* Process
         *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
         *  |------------------------------------------------------------------------------------------|---------------|
         *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
         *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
         *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
         *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
         *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
         *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
         *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
         *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
         *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
         *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
         *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
         *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
         *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
         */
        int count = 0;
        int head = 0;
        int retHead = 0;
        int retTail = 0;
        int minLen = numeric_limits<int>::max();
        for (int i = 0; i < sSize; ++i) {
            // update hash set by character in s
            --hashSet[s[i]];

            // if character both in t and s
            if (hashSet[s[i]] >= 0) {
                ++count;
            }

            while (count == tSize) {
                // update head and tail according to Minimum record
                if ((i - head + 1) < minLen) {
                    minLen = i - head + 1;
                    retHead = head;
                    retTail = i;
                }

                // update hash set by character in s
                ++hashSet[s[head]];

                // if character in s
                if (hashSet[s[head]] > 0) {
                    --count;
                }

                // move head
                head++;
            }
        }
        if (minLen != numeric_limits<int>::max()) {
            s[retTail + 1] = 0;
            retVal = &(s[retHead]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"a", "aa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ADOBECODEBANC", t = "ABC"
     *  Output: "BANC"
     *
     *  Input: s = "a", t = "a"
     *  Output: "a"
     *
     *  Input: s = "a", t = "aa"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\n";

        answer = cSolution.minWindow(testData[i].s, testData[i].t);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
