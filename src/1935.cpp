#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
   public:
    int canBeTypedWords(string text, string brokenLetters) {
        int retVal = 0;

        vector<string> words;
        string word;
        istringstream in(text);
        while (in >> word) {
            words.push_back(word);
        }

        for (const string& word : words) {
            if (word.find_first_of(brokenLetters) == string::npos) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string text;
        string brokenLetters;
    };
    vector<subject> testData{{"hello world", "ad"}, {"leet code", "lt"}, {"leet code", "e"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: text = "hello world", brokenLetters = "ad"
     *  Output: 1
     *
     *  Input: text = "leet code", brokenLetters = "lt"
     *  Output: 1
     *
     *  Input: text = "leet code", brokenLetters = "e"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: text = \"" << testData[i].text << "\", brokenLetters = \"" << testData[i].brokenLetters
             << "\"\n";

        answer = cSolution.canBeTypedWords(testData[i].text, testData[i].brokenLetters);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
