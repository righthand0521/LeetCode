#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    int case2Helper(string& s, char x, char y) {
        int retVal = 0;

        int sSize = s.size();
        unordered_map<int, int> h;
        for (int i = 0; i < sSize; i++) {
            if ((s[i] != x) && (s[i] != y)) {
                continue;
            }

            h.clear();
            h[0] = i - 1;
            int diff = 0;
            while ((i < sSize) && ((s[i] == x) || (s[i] == y))) {
                diff += (s[i] == x) ? (1) : (-1);
                if (h.find(diff) != h.end()) {
                    retVal = max(retVal, i - h[diff]);
                } else {
                    h[diff] = i;
                }

                i++;
            }
        }

        return retVal;
    }
    long long getId(int x, int y, int sSize) {
        long long retVal = 1ll * (x + sSize) << 32 | (y + sSize);

        return retVal;
    }

   public:
    int longestBalanced(string s) {
        int retVal = 0;

        int sSize = s.size();

        // Case 1: single character
        int last = 0;
        for (int i = 0; i < sSize; i++) {
            if ((i > 0) && (s[i] == s[i - 1])) {
                last++;
            } else {
                last = 1;
            }

            retVal = max(retVal, last);
        }

        // Case 2: two distinct characters
        retVal = max(retVal, case2Helper(s, 'a', 'b'));
        retVal = max(retVal, case2Helper(s, 'b', 'c'));
        retVal = max(retVal, case2Helper(s, 'a', 'c'));

        // Case 3: all three characters
        unordered_map<long long, int> h = {{getId(0, 0, sSize), -1}};
        int pre[3] = {0, 0, 0};
        for (int i = 0; i < sSize; i++) {
            pre[s[i] - 'a']++;

            long long id = getId(pre[1] - pre[0], pre[1] - pre[2], sSize);
            if (h.find(id) != h.end()) {
                retVal = max(retVal, i - h[id]);
            } else {
                h[id] = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abbac"}, {"aabcc"}, {"aba"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abbac"
     *  Output: 4
     *
     *  Input: s = "aabcc"
     *  Output: 3
     *
     *  Input: s = "aba"
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.longestBalanced(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
