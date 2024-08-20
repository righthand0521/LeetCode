#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> retVal;

        int wordsSize = words.size();
        int wordLength = words[0].size();
        int sLength = s.size();
        for (int i = 0; ((i < wordLength) && (i + wordsSize * wordLength <= sLength)); ++i) {
            unordered_map<string, int> differ;
            for (int j = 0; j < wordsSize; ++j) {
                ++differ[s.substr(i + j * wordLength, wordLength)];
            }

            for (string& word : words) {
                if (--differ[word] == 0) {
                    differ.erase(word);
                }
            }

            for (int start = i; start < sLength - wordsSize * wordLength + 1; start += wordLength) {
                if (start != i) {
                    string word = s.substr(start + (wordsSize - 1) * wordLength, wordLength);

                    if (++differ[word] == 0) {
                        differ.erase(word);
                    }

                    word = s.substr(start - wordLength, wordLength);

                    if (--differ[word] == 0) {
                        differ.erase(word);
                    }
                }

                if (differ.empty() == true) {
                    retVal.emplace_back(start);
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
    vector<subject> testData{{"barfoothefoobarman", {"foo", "bar"}},
                             {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}},
                             {"barfoofoobarthefoobarman", {"bar", "foo", "the"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "barfoothefoobarman", words = ["foo","bar"]
     *  Output: [0,9]
     *
     *  Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
     *  Output: []
     *
     *  Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
     *  Output: [6,9,12]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.findSubstring(testData[i].s, testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
