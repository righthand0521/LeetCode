#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define HASH_MAP (0)
#define TWO_DIMENSIONAL_ARRAY (1)
class Solution {
   public:
    int longestPalindrome(vector<string>& words) {
        int retVal = 0;

        bool central = false;

#if (HASH_MAP)
        cout << "A Hash Map Approach"
             << "\n";

        unordered_map<string, int> count;
        for (const string& word : words) {
            count[word]++;
        }

        for (const auto& [word, countOfTheWord] : count) {
            // if the word is a palindrome
            if (word[0] == word[1]) {
                if (countOfTheWord % 2 == 0) {
                    retVal += countOfTheWord;
                } else {
                    retVal += countOfTheWord - 1;
                    central = true;
                }
                // consider a pair of non-palindrome words such that one is the
                // reverse of another ({word[1], word[0]} is the reversed word)
            } else if (word[0] < word[1] && count.count({word[1], word[0]})) {
                retVal += 2 * min(countOfTheWord, count[{word[1], word[0]}]);
            }
        }
#elif (TWO_DIMENSIONAL_ARRAY)
        cout << "A Two-Dimensional Array Approach"
             << "\n";

        constexpr int alphabetSize = 26;
        vector count(alphabetSize, vector<int>(alphabetSize));
        for (const string& word : words) {
            count[word[0] - 'a'][word[1] - 'a']++;
        }

        for (int i = 0; i < alphabetSize; ++i) {
            if (count[i][i] % 2 == 0) {
                retVal += count[i][i];
            } else {
                retVal += count[i][i] - 1;
                central = true;
            }
            for (int j = (i + 1); j < alphabetSize; ++j) {
                retVal += (2 * min(count[i][j], count[j][i]));
            }
        }
#endif

        if (central) {
            retVal++;
        }
        retVal *= 2;

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
