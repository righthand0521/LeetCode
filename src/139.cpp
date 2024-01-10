#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        bool retVal = false;

        int sSize = s.size();

        vector<bool> dp(sSize + 1, false);
        dp[0] = true;
        for (int i = 1; i <= sSize; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] == false) {
                    continue;
                }
                for (auto word : wordDict) {
                    if (s.substr(j, i - j) == word) {
                        dp[i] = true;
                        j = i;
                        break;
                    }
                }
            }
        }
        retVal = dp[sSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<string> wordDict;
    };
    vector<subject> testData{{"leetcode", {"leet", "code"}},
                             {"applepenapple", {"apple", "pen"}},
                             {"catsandog", {"cats", "dog", "sand", "and", "cat"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leetcode", wordDict = ["leet","code"]
     *  Output: true
     *
     *  Input: s = "applepenapple", wordDict = ["apple","pen"]
     *  Output: true
     *
     *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", wordDict = [";
        for (long unsigned int j = 0; j < testData[i].wordDict.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].wordDict[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.wordBreak(testData[i].s, testData[i].wordDict);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
