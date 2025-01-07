#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> computeLPSArray(string &substring) {
        vector<int> retVal;

        int substringSize = substring.size();
        retVal.assign(substringSize, 0);

        int length = 0;
        int currentIndex = 1;
        while (currentIndex < substringSize) {
            if (substring[currentIndex] == substring[length]) {
                length++;
                retVal[currentIndex] = length;
                currentIndex++;
                continue;
            }

            if (length > 0) {
                length = retVal[length - 1];  // Backtrack using LPS array to find a shorter match.
            } else {
                currentIndex++;
            }
        }

        return retVal;
    }
    bool isSubstringOf(string &substring, string &main, vector<int> &lps) {
        bool retVal = false;

        int mainSize = main.size();
        int substringSize = substring.size();
        int mainIndex = 0;
        int substringIndex = 0;
        while (mainIndex < mainSize) {
            if (main[mainIndex] == substring[substringIndex]) {
                substringIndex++;
                mainIndex++;
                if (substringIndex == substringSize) {
                    retVal = true;
                    return retVal;
                }
                continue;
            }

            if (substringIndex > 0) {
                substringIndex = lps[substringIndex - 1];  // Use the LPS to skip unnecessary comparisons.
            } else {
                mainIndex++;
            }
        }

        return retVal;
    }

   public:
    vector<string> stringMatching(vector<string> &words) {
        vector<string> retVal;

        int wordsSize = words.size();
        for (int currentWordIndex = 0; currentWordIndex < wordsSize; currentWordIndex++) {
            vector<int> lps = computeLPSArray(words[currentWordIndex]);

            // Compare the current word with all other words.
            for (int otherWordIndex = 0; otherWordIndex < wordsSize; otherWordIndex++) {
                if (currentWordIndex == otherWordIndex) {
                    continue;  // Skip comparing the word with itself.
                }

                // Check if the current word is a substring of another word.
                if (isSubstringOf(words[currentWordIndex], words[otherWordIndex], lps) == true) {
                    retVal.emplace_back(words[currentWordIndex]);
                    break;  // No need to check further for this word.
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{
        {{"mass", "as", "hero", "superhero"}}, {{"leetcode", "et", "code"}}, {{"blue", "green", "bu"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["mass","as","hero","superhero"]
     *  Output: ["as","hero"]
     *
     *  Input: words = ["leetcode","et","code"]
     *  Output: ["et","code"]
     *
     *  Input: words = ["blue","green","bu"]
     *  Output: []
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.stringMatching(testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
