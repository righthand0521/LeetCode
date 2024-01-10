#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        bool retVal = false;

        string words1 = "";
        for (string w : word1) {
            words1 += w;
        }

        string words2 = "";
        for (string w : word2) {
            words2 += w;
        }

        if (words1 == words2) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> word1;
        vector<string> word2;
    };
    vector<subject> testData{
        {{"ab", "c"}, {"a", "bc"}}, {{"a", "cb"}, {"ab", "c"}}, {{"abc", "d", "defg"}, {"abcddefg"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
     *  Output: true
     *
     *  Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
     *  Output: false
     *
     *  Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word1 = [";
        for (long unsigned int j = 0; j < testData[i].word1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].word1[j] << "\"";
        }
        cout << "], word2 = [";
        for (long unsigned int j = 0; j < testData[i].word2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].word2[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.arrayStringsAreEqual(testData[i].word1, testData[i].word2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
