#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countPrefixSuffixPairs(vector<string>& words) {
        int retVal = 0;

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize; ++i) {
            for (int j = i + 1; j < wordsSize; ++j) {
                string str1 = words[i];
                string str2 = words[j];
                if (str1.size() > str2.size()) {
                    continue;
                }

                if ((str2.find(str1) == 0) && (str2.rfind(str1) == str2.size() - str1.size())) {
                    ++retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{{{"a", "aba", "ababa", "aa"}}, {{"pa", "papa", "ma", "mama"}}, {{"abab", "ab"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["a","aba","ababa","aa"]
     *  Output: 4
     *
     *  Input: words = ["pa","papa","ma","mama"]
     *  Output: 2
     *
     *  Input: words = ["abab","ab"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.countPrefixSuffixPairs(testData[i].words);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
