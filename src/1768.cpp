#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string mergeAlternately(string word1, string word2) {
        string retVal = "";

        int idx1 = 0;
        int word1Size = word1.size();
        int idx2 = 0;
        int word2Size = word2.size();
        while ((idx1 < word1Size) || (idx2 < word2Size)) {
            if (idx1 < word1Size) {
                retVal += word1[idx1++];
            }

            if (idx2 < word2Size) {
                retVal += word2[idx2++];
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word1;
        string word2;
    };
    vector<subject> testData{{"abc", "pqr"}, {"ab", "pqrs"}, {"abcd", "pq"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word1 = "abc", word2 = "pqr"
     *  Output: "apbqcr"
     *
     *  Input: word1 = "ab", word2 = "pqrs"
     *  Output: "apbqrs"
     *
     *  Input: word1 = "abcd", word2 = "pq"
     *  Output: "apbqcd"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word1 = \"" << testData[i].word1 << "\", word2 = \"" << testData[i].word2 << "\"\n";

        answer = cSolution.mergeAlternately(testData[i].word1, testData[i].word2);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
