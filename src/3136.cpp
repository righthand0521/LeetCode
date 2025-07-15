#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValid(string word) {
        bool retVal = false;

        int wordSize = word.size();
        if (wordSize < 3) {
            return retVal;
        }

        bool hasVowel = false;
        bool hasConsonant = false;
        for (char c : word) {
            if (isalpha(c)) {
                c = tolower(c);
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                    hasVowel = true;
                } else {
                    hasConsonant = true;
                }
            } else if (isdigit(c)) {
                continue;
            } else {
                return retVal;
            }
        }
        retVal = hasVowel && hasConsonant;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"234Adas"}, {"b3"}, {"a3$e"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "234Adas"
     *  Output: true
     *
     *  Input: word = "b3"
     *  Output: false
     *
     *  Input: word = "a3$e"
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.isValid(testData[i].word);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
