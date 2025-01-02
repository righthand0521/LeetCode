#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.assign(queriesSize, 0);

        int wordsSize = words.size();
        vector<int> prefixSum(wordsSize, 0);

        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
        int vowelCount = 0;
        for (int i = 0; i < wordsSize; i++) {
            string word = words[i];
            int wordSize = word.size();
            if ((vowels.count(word[0])) && (vowels.count(word[wordSize - 1]))) {
                vowelCount++;
            }
            prefixSum[i] = vowelCount;
        }

        for (int i = 0; i < queriesSize; i++) {
            vector<int> query = queries[i];
            retVal[i] = prefixSum[query[1]];
            if (query[0] != 0) {
                retVal[i] -= prefixSum[query[0] - 1];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{"aba", "bcb", "ece", "aa", "e"}, {{0, 2}, {1, 4}, {1, 1}}},
                             {{"a", "e", "i"}, {{0, 2}, {0, 1}, {2, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
     *  Output: [2,3,0]
     *
     *  Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
     *  Output: [3,2,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.vowelStrings(testData[i].words, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
