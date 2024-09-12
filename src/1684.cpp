#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int retVal = 0;

        vector<int> allowedChars(26, 0);  // words[i] and allowed contain only lowercase English letters.
        for (char c : allowed) {
            allowedChars[c - 'a'] = 1;
        }

        for (string word : words) {
            int isConsistent = 1;
            for (char c : word) {
                if (allowedChars[c - 'a'] == 0) {
                    isConsistent = 0;
                    break;
                }
            }
            if (isConsistent == 1) {
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string allowed;
        vector<string> words;
    };
    vector<subject> testData{{"ab", {"ad", "bd", "aaab", "baa", "badab"}},
                             {"abc", {"a", "b", "c", "ab", "ac", "bc", "abc"}},
                             {"cad", {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
     *  Output: 2
     *
     *  Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
     *  Output: 7
     *
     *  Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: allowed = \"" << testData[i].allowed << "\", words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.countConsistentStrings(testData[i].allowed, testData[i].words);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
