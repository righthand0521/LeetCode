#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string compressedString(string word) {
        string retVal;

        int wordSize = word.size();

        int count = 1;
        for (int i = 1; i < wordSize; ++i) {
            if ((word[i] == word[i - 1]) && (count < 9)) {
                count++;
                continue;
            }
            retVal += (to_string(count) + word[i - 1]);
            count = 1;
        }
        retVal += (to_string(count) + word[wordSize - 1]);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"abcde"}, {"aaaaaaaaaaaaaabb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "abcde"
     *  Output: "1a1b1c1d1e"
     *
     *  Input: word = "aaaaaaaaaaaaaabb"
     *  Output: "9a5a2b"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.compressedString(testData[i].word);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
