#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> split(string &str, char ch) {
        vector<string> retVal;

        string s(str);
        int sSize = s.size();

        int pos = 0;
        int start = 0;
        while (pos < sSize) {
            while ((pos < sSize) && (s[pos] == ch)) {
                pos++;
            }
            start = pos;
            while ((pos < sSize) && (s[pos] != ch)) {
                pos++;
            }

            if (start < sSize) {
                retVal.emplace_back(s.substr(start, pos - start));
            }
        }

        return retVal;
    }
    string replaceWords(vector<string> &dictionary, string sentence) {
        string retVal;

        unordered_set<string> dictionarySet;
        for (auto &root : dictionary) {
            dictionarySet.emplace(root);
        }

        vector<string> words = split(sentence, ' ');
        for (auto &word : words) {
            int wordSize = word.size();
            for (int i = 0; i < wordSize; i++) {
                if (dictionarySet.count(word.substr(0, 1 + i)) != 0) {
                    word = word.substr(0, 1 + i);
                    break;
                }
            }
        }

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize - 1; i++) {
            retVal.append(words[i]);
            retVal.append(" ");
        }
        retVal.append(words.back());

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<string> dictionary;
        string sentence;
    };
    vector<subject> testData{{{"cat", "bat", "rat"}, "the cattle was rattled by the battery"},
                             {{"a", "b", "c"}, "aadsfasf absbs bbab cadsfafs"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
     *  Output: "the cat was rat by the bat"
     *
     *  Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
     *  Output: "a a b c"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dictionary = [";
        for (long unsigned int j = 0; j < testData[i].dictionary.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].dictionary[j] << "\"";
        }
        cout << "], sentence = \"" << testData[i].sentence << "\"\n";

        answer = cSolution.replaceWords(testData[i].dictionary, testData[i].sentence);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
