#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxFreqSum(string s) {
        int retVal = 0;

        const int ALPHABET_SIZE = 26;  // s consists of lowercase English letters only.
        vector<int> frequency(ALPHABET_SIZE, 0);
        for (char c : s) {
            frequency[c - 'a']++;
        }

        int vowel = 0;
        int consonant = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (frequency[i] <= 0) {
                continue;
            }

            char c = 'a' + i;
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowel = max(vowel, frequency[i]);
            } else {
                consonant = max(consonant, frequency[i]);
            }
        }
        retVal = vowel + consonant;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"successes"}, {"aeiaeia"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "successes"
     *  Output: 6
     *
     *  Input: s = "aeiaeia"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxFreqSum(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
