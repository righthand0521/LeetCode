#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findTheLongestSubstring(string s) {
        int retVal = 0;

        vector<int> characterMap(26, 0);  // s contains only lowercase English letters.
        characterMap['a' - 'a'] = 1;
        characterMap['e' - 'a'] = 2;
        characterMap['i' - 'a'] = 4;
        characterMap['o' - 'a'] = 8;
        characterMap['u' - 'a'] = 16;
        vector<int> mp(32, -1);  // 1 + 2 + 4 + 8 + 16 = 31 < 32

        int sSize = s.size();
        int prefixXOR = 0;
        for (int i = 0; i < sSize; ++i) {
            prefixXOR ^= characterMap[s[i] - 'a'];
            if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
                mp[prefixXOR] = i;
            }
            retVal = max(retVal, i - mp[prefixXOR]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"eleetminicoworoep"}, {"leetcodeisgreat"}, {"bcbcbc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "eleetminicoworoep"
     *  Output: 13
     *
     *  Input: s = "leetcodeisgreat"
     *  Output: 5
     *
     *  Input: s = "bcbcbc"
     *  Output: 6
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.findTheLongestSubstring(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
