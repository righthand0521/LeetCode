#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSubsequence(string s, int k) {
        int retVal = 0;

        int sm = 0;
        int bits = 32 - __builtin_clz(k);
        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            char ch = s[sSize - 1 - i];
            if (ch == '1') {
                if ((i < bits) && (sm + (1 << i) <= k)) {
                    sm += (1 << i);
                    retVal++;
                }
            } else {
                retVal++;
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
    vector<subject> testData{{"1001010", 5}, {"00101001", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1001010", k = 5
     *  Output: 5
     *
     *  Input: s = "00101001", k = 1
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.longestSubsequence(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
