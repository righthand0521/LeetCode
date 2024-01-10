#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int retVal = 0;

        int wordsSize = words.size();

        vector<queue<pair<int, int>>> record(26);  // s and words[i] consist of only lowercase English letters.
        for (int i = 0; i < wordsSize; ++i) {
            record[words[i][0] - 'a'].emplace(i, 0);
        }

        for (char c : s) {
            auto& entry = record[c - 'a'];
            int size = entry.size();
            while (size--) {
                auto [wordsIndex, idx] = entry.front();
                entry.pop();

                int wordLength = words[wordsIndex].size();
                ++idx;
                if (idx == wordLength) {
                    ++retVal;
                } else {
                    record[words[wordsIndex][idx] - 'a'].emplace(wordsIndex, idx);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<string> words;
    };
    vector<subject> testData{{"abcde", {"a", "bb", "acd", "ace"}},
                             {"dsahjpjauf", {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcde", words = ["a","bb","acd","ace"]
     *  Output: 3
     *
     *  Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.numMatchingSubseq(testData[i].s, testData[i].words);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
