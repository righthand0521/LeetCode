#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool check(string& s1, string& s2) {
        bool retVal = false;

        int s1Size = s1.size();
        int s2Size = s2.size();
        if (s1Size != s2Size) {
            return retVal;
        }

        int diff = 0;
        for (int i = 0; i < s1Size; i++) {
            if (s1[i] != s2[i]) {
                diff++;
            }
            if (diff > 1) {
                return retVal;
            }
        }
        if (diff == 1) {
            retVal = true;
        }

        return retVal;
    }

   public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        vector<string> retVal;

        int groupsSize = groups.size();

        vector<int> dp(groupsSize, 1);
        vector<int> prev(groupsSize, -1);
        int maxIndex = 0;
        for (int i = 1; i < groupsSize; i++) {
            for (int j = 0; j < i; j++) {
                if ((check(words[i], words[j]) == 1) && (dp[j] + 1 > dp[i]) && (groups[i] != groups[j])) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
            if (dp[i] > dp[maxIndex]) {
                maxIndex = i;
            }
        }

        for (int i = maxIndex; i >= 0; i = prev[i]) {
            retVal.emplace_back(words[i]);
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        vector<int> groups;
    };
    vector<subject> testData{{{"bab", "dab", "cab"}, {1, 2, 2}}, {{"a", "b", "c", "d"}, {1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["bab","dab","cab"], groups = [1,2,2]
     *  Output: ["bab","cab"]
     *
     *  Input: words = ["a","b","c","d"], groups = [1,2,3,4]
     *  Output: ["a","b","c","d"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], groups = [";
        for (long unsigned int j = 0; j < testData[i].groups.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].groups[j];
        }
        cout << "]\n";

        answer = cSolution.getWordsInLongestSubsequence(testData[i].words, testData[i].groups);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
