#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numWays(vector<string>& words, string target) {
        int retVal = 0;

        int targetSize = target.size();
        vector<long> dp(targetSize + 1, 0);
        dp[0] = 1;
        for (long unsigned int i = 0; i < words[0].size(); ++i) {
            vector<int> count(26);  // words[i] and target contain only lowercase English letters.
            for (auto& word : words) {
                count[word[i] - 'a']++;
            }

            for (int j = targetSize - 1; j >= 0; --j) {
                dp[j + 1] += dp[j] * count[target[j] - 'a'] % MODULO;
            }
        }
        retVal = dp[targetSize] % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        string target;
    };
    vector<subject> testData{{{"acca", "bbbb", "caca"}, "aba"}, {{"abba", "baab"}, "bab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["acca","bbbb","caca"], target = "aba"
     *  Output: 6
     *
     *  Input: words = ["abba","baab"], target = "bab"
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], target = \"" << testData[i].target << "\"\n";

        answer = cSolution.numWays(testData[i].words, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
