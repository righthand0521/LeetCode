#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> retVal;

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize; ++i) {
            int wordSize = words[i].size();
            for (int j = 0; j < wordSize; ++j) {
                if (words[i][j] == x) {
                    retVal.emplace_back(i);
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        char x;
    };
    vector<subject> testData{
        {{"leet", "code"}, 'e'}, {{"abc", "bcd", "aaaa", "cbc"}, 'a'}, {{"abc", "bcd", "aaaa", "cbc"}, 'z'}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["leet","code"], x = "e"
     *  Output: [0,1]
     *
     *  Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
     *  Output: [0,2]
     *
     *  Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
     *  Output: []
     */

    // Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], x = \"" << testData[i].x << "\"\n";

        Solution cSolution;
        answer = cSolution.findWordsContaining(testData[i].words, testData[i].x);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
