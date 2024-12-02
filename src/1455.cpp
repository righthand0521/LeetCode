#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int retVal = -1;

        int idx = 0;
        int searchWordSize = searchWord.size();
        int searchWordIdx = 0;
        bool startSearch = true;
        for (char c : sentence) {
            if (c == ' ') {
                idx++;
                searchWordIdx = 0;
                startSearch = true;
                continue;
            } else if (startSearch == false) {
                continue;
            }

            if (c == searchWord[searchWordIdx]) {
                searchWordIdx++;
                if (searchWordIdx == searchWordSize) {
                    retVal = idx + 1;
                    break;
                }
            } else {
                searchWordIdx = 0;
                startSearch = false;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string sentence;
        string searchWord;
    };
    vector<subject> testData{
        {"i love eating burger", "burg"}, {"this problem is an easy problem", "pro"}, {"i am tired", "you"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: sentence = "i love eating burger", searchWord = "burg"
     *  Output: 4
     *
     *  Input: sentence = "this problem is an easy problem", searchWord = "pro"
     *  Output: 2
     *
     *  Input: sentence = "i am tired", searchWord = "you"
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: sentence = \"" << testData[i].sentence << "\", k = \"" << testData[i].searchWord << "\"\n";

        answer = cSolution.isPrefixOfWord(testData[i].sentence, testData[i].searchWord);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
