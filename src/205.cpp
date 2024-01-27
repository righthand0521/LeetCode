#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isIsomorphic(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize != tSize) {
            return retVal;
        }

        unordered_map<char, char> hashTableS;
        unordered_map<char, char> hashTableT;
        for (int i = 0; i < sSize; ++i) {
            if ((hashTableS.count(s[i]) != 0) && (hashTableS[s[i]] != t[i])) {
                return retVal;
            } else if ((hashTableT.count(t[i]) != 0) && (hashTableT[t[i]] != s[i])) {
                return retVal;
            } else {
                hashTableS[s[i]] = t[i];
                hashTableT[t[i]] = s[i];
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"egg", "add"},
                             {"foo", "bar"},
                             {"paper", "title"},
                             {"badc", "baba"},
                             {"abcdefghijklmnopqrstuvwxyzva", "abcdefghijklmnopqrstuvwxyzck"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "egg", t = "add"
     *  Output: true
     *
     *  Input: s = "foo", t = "bar"
     *  Output: false
     *
     *  Input: s = "paper", t = "title"
     *  Output: true
     *
     *  Input: s = "badc", t = "baba"
     *  Output: false
     *
     *  Input: s = "abcdefghijklmnopqrstuvwxyzva", t = "abcdefghijklmnopqrstuvwxyzck"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.isIsomorphic(testData[i].s, testData[i].t);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
