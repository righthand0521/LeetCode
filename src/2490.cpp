#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isCircularSentence(string sentence) {
        bool retVal = false;

        int sentenceSize = sentence.size();
        if (sentence[0] != sentence[sentenceSize - 1]) {
            return retVal;
        }
        // A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
        for (int i = 0; i < sentenceSize; ++i) {
            if ((sentence[i] == ' ') && (sentence[i - 1] != sentence[i + 1])) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string sentence;
    };
    vector<subject> testData{{"leetcode exercises sound delightful"}, {"eetcode"}, {"Leetcode is cool"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: sentence = "leetcode exercises sound delightful"
     *  Output: true
     *
     *  Input: sentence = "eetcode"
     *  Output: true
     *
     *  Input: sentence = "Leetcode is cool"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: sentence = \"" << testData[i].sentence << "\"\n";

        answer = cSolution.isCircularSentence(testData[i].sentence);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
