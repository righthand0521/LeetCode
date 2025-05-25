#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestPalindrome(vector<string>& words) {
        int retVal = 0;

        unordered_map<string, int> frequency;
        for (const string& word : words) {
            frequency[word]++;
        }

        bool middle = false;
        for (const auto& [word, count] : frequency) {
            string reverseWord = string(1, word[1]) + word[0];
            if (word == reverseWord) {
                if (count % 2 == 1) {
                    middle = true;
                }
                retVal += (2 * (count / 2 * 2));
            } else if (word > reverseWord) {
                retVal += (4 * min(count, frequency[reverseWord]));
            }
        }
        if (middle == true) {
            retVal += 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{{{"lc", "cl", "gg"}}, {{"ab", "ty", "yt", "lc", "cl", "ab"}}, {{"cc", "ll", "xx"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["lc","cl","gg"]
     *  Output: 6
     *
     *  Input: words = ["ab","ty","yt","lc","cl","ab"]
     *  Output: 8
     *
     *  Input: words = ["cc","ll","xx"]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.longestPalindrome(testData[i].words);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
