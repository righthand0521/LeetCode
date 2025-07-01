#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int possibleStringCount(string word) {
        int retVal = 1;

        int wordSize = word.size();
        for (int i = 1; i < wordSize; ++i) {
            if (word[i - 1] == word[i]) {
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"abbcccc"}, {"abcd"}, {"aaaa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "abbcccc"
     *  Output: 5
     *
     *  Input: word = "abcd"
     *  Output: 1
     *
     *  Input: word = "aaaa"
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.possibleStringCount(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
