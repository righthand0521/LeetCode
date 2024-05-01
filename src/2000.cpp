#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string reversePrefix(string word, char ch) {
        string retVal = word;

        size_t index = word.find(ch);
        if (index == string::npos) {
            return retVal;
        }
        reverse(retVal.begin(), retVal.begin() + index + 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
        char ch;
    };
    vector<subject> testData{{"abcdefd", 'd'}, {"xyxzxe", 'z'}, {"abcd", 'z'}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "abcdefd", ch = "d"
     *  Output: "dcbaefd"
     *
     *  Input: word = "xyxzxe", ch = "z"
     *  Output: "zxyxxe"
     *
     *  Input: word = "abcd", ch = "z"
     *  Output: "abcd"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\", ch = \"" << testData[i].ch << "\"\n";

        answer = cSolution.reversePrefix(testData[i].word, testData[i].ch);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
