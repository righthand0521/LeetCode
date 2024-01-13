#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSteps(string s, string t) {
        int retVal = 0;

        int sSize = s.size();  // s and t consist of lowercase English letters only.

        unordered_map<char, int> hashTable;
        for (int i = 0; i < sSize; ++i) {
            ++hashTable[s[i]];
            --hashTable[t[i]];
        }

        for (auto [key, value] : hashTable) {
            if (value > 0) {
                retVal += value;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"bab", "aba"}, {"leetcode", "practice"}, {"anagram", "mangaar"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "bab", t = "aba"
     *  Output: 1
     *
     *  Input: s = "leetcode", t = "practice"
     *  Output: 5
     *
     *  Input: s = "anagram", t = "mangaar"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.minSteps(testData[i].s, testData[i].t);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
