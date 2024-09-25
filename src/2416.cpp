#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    TrieNode* next[26] = {};  // words[i] consists of lowercase English letters.
    int cnt = 0;
};
class Solution {
    TrieNode root;

   public:
    void insert(string word) {
        auto node = &root;
        for (char c : word) {
            if (node->next[c - 'a'] == nullptr) {
                node->next[c - 'a'] = new TrieNode();
            }
            node->next[c - 'a']->cnt++;
            node = node->next[c - 'a'];
        }
    }
    int count(string s) {
        int retVal = 0;

        auto node = &root;
        for (char c : s) {
            retVal += node->next[c - 'a']->cnt;
            node = node->next[c - 'a'];
        }

        return retVal;
    }
    vector<int> sumPrefixScores(vector<string>& words) {
        vector<int> retVal;

        int wordsSize = words.size();

        for (int i = 0; i < wordsSize; i++) {
            insert(words[i]);
        }

        retVal.resize(wordsSize, 0);
        for (int i = 0; i < wordsSize; i++) {
            retVal[i] = count(words[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{{{"abc", "ab", "bc", "b"}}, {{"abcd"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["abc","ab","bc","b"]
     *  Output: [5,4,3,2]
     *
     *  Input: words = ["abcd"]
     *  Output: [4]
     */

    // Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        Solution cSolution;
        answer = cSolution.sumPrefixScores(testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
