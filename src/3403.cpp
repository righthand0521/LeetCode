#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    string lastSubstring(string s) {
        string retVal = "";

        int sSize = s.size();
        int i = 0;
        int j = 1;
        while (j < sSize) {
            int k = 0;
            while ((j + k < sSize) && (s[i + k] == s[j + k])) {
                k++;
            }

            if ((j + k < sSize) && (s[i + k] < s[j + k])) {
                int tmp = i;
                i = j;
                j = max(j + 1, tmp + k + 1);
            } else {
                j = j + k + 1;
            }
        }
        retVal = s.substr(i, sSize - i);

        return retVal;
    }

   public:
    string answerString(string word, int numFriends) {
        string retVal = word;

        if (numFriends == 1) {
            return retVal;
        }

        string last = lastSubstring(word);
        int lastSize = last.size();
        int wordSize = word.size();
        retVal = last.substr(0, min(lastSize, wordSize - numFriends + 1));

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
        int numFriends;
    };
    vector<subject> testData{{"dbca", 2}, {"gggg", 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "dbca", numFriends = 2
     *  Output: "dbc"
     *
     *  Input: word = "gggg", numFriends = 4
     *  Output: "g"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\", numFriends = " << testData[i].numFriends << "\n";

        answer = cSolution.answerString(testData[i].word, testData[i].numFriends);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
