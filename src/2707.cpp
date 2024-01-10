#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int retVal = 0;

        unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());

        int sSize = s.length();
        vector<int> dp(sSize + 1, 0);
        for (int start = sSize - 1; start >= 0; start--) {
            dp[start] = dp[start + 1] + 1;
            for (int end = start; end < sSize; end++) {
                auto curr = s.substr(start, end - start + 1);
                if (dictionarySet.count(curr)) {
                    dp[start] = min(dp[start], dp[end + 1]);
                }
            }
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<string> dictionary;
    };
    vector<subject> testData{{"leetscode", {"leet", "code", "leetcode"}}, {"sayhelloworld", {"hello", "world"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
     *  Output: 1
     *
     *  Input: s = "sayhelloworld", dictionary = ["hello","world"]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", dictionary = [";
        for (long unsigned int j = 0; j < testData[i].dictionary.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].dictionary[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.minExtraChar(testData[i].s, testData[i].dictionary);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
