#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string sortVowels(string s) {
        string retVal;

        vector<char> vowels;
        for (char c : s) {
            if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U') || (c == 'a') || (c == 'e') ||
                (c == 'i') || (c == 'o') || (c == 'u')) {
                vowels.emplace_back(c);
            }
        }
        sort(vowels.begin(), vowels.end());

        int idx = 0;
        for (char c : s) {
            if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U') || (c == 'a') || (c == 'e') ||
                (c == 'i') || (c == 'o') || (c == 'u')) {
                retVal += vowels[idx++];
            } else {
                retVal += c;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"lEetcOde"}, {"lYmpH"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "lEetcOde"
     *  Output: "lEOtcede"
     *
     *  Input: s = "lYmpH"
     *  Output: "lYmpH"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.sortVowels(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
