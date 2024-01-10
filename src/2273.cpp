#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> retVal;

        int idx = 0;
        retVal.push_back(words[0]);

        int len = words.size();
        for (int i = 1; i < len; ++i) {
            string ret = retVal[idx];
            string ori = words[i];
            sort(ret.begin(), ret.end());
            sort(ori.begin(), ori.end());
            if (ret.compare(ori) == 0) {
                continue;
            }

            ++idx;
            retVal.push_back(words[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{{{"abba", "baba", "bbaa", "cd", "cd"}},
                             {{"a", "b", "c", "d", "e"}},
                             {{"z", "z", "z", "gsw", "wsg", "gsw", "krptu"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["abba","baba","bbaa","cd","cd"]
     *  Output: ["abba","cd"]
     *
     *  Input: words = ["a","b","c","d","e"]
     *  Output: ["a","b","c","d","e"]
     *
     *  Input: words = ["z", "z", "z", "gsw", "wsg", "gsw", "krptu"]
     *  Output: ["z","gsw","krptu"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.removeAnagrams(testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
