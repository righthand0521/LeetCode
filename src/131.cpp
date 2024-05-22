#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int isPalindrome(string &s, vector<vector<int>> &dp, int i, int j) {
        int retVal = dp[i][j];

        if (dp[i][j] != 0) {
            return retVal;
        }

        if (i >= j) {
            dp[i][j] = 1;
        } else {
            dp[i][j] = (s[i] == s[j] ? isPalindrome(s, dp, i + 1, j - 1) : -1);
        }
        retVal = dp[i][j];

        return retVal;
    }
    void dfs(string &s, int idx, vector<vector<int>> &dp, vector<vector<string>> &retVal, vector<string> &answer) {
        int sSize = s.size();

        if (idx == sSize) {
            retVal.push_back(answer);
            return;
        }

        for (int j = idx; j < sSize; ++j) {
            if (isPalindrome(s, dp, idx, j) == 1) {
                answer.push_back(s.substr(idx, j - idx + 1));
                dfs(s, j + 1, dp, retVal, answer);
                answer.pop_back();
            }
        }
    }

   public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> retVal;

        int sSize = s.size();

        /* Dynamic Programming Preprocessing
         *  f(i,j): s[i..j] is Palindrome or not
         *            | True, i≥j
         *  f(i,j) = <
         *            | f(i+1, j−1) ∧ (s[i]=s[j]), otherwise
         */
        vector<vector<int>> dp(sSize, vector<int>(sSize, 1));
        for (int i = sSize - 1; i >= 0; --i) {
            for (int j = i + 1; j < sSize; ++j) {
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }

        vector<string> answer;
        dfs(s, 0, dp, retVal, answer);

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aab"}, {"a"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aab"
     *  Output: [["a","a","b"],["aa","b"]]
     *
     *  Input: s = "a"
     *  Output: [["a"]]
     */

    Solution cSolution;
    vector<vector<string>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.partition(testData[i].s);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << answer[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
