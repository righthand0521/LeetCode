#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDistance(string word1, string word2) {
        int retVal = 0;

        int word1Size = word1.size();
        int word2Size = word2.size();
        vector<vector<int>> dp(word1Size + 1, vector<int>(word2Size + 1));

        /* Example: Input: word1 = "horse", word2 = "ros"
         *      r o s
         *    0 1 2 3
         *  h 1 1 2 3
         *  o 2 2 1 2
         *  r 3 2 2 2
         *  s 4 3 3 2
         *  e 5 4 4 3
         */
        for (int idx1 = 0; idx1 <= word1Size; ++idx1) {
            dp[idx1][0] = idx1;
        }
        for (int idx2 = 0; idx2 <= word2Size; ++idx2) {
            dp[0][idx2] = idx2;
        }
        for (int idx1 = 1; idx1 <= word1Size; ++idx1) {
            for (int idx2 = 1; idx2 <= word2Size; ++idx2) {
                int insertOperations = dp[idx1][idx2 - 1];
                int deleteOperations = dp[idx1 - 1][idx2];
                int replaceOperations = dp[idx1 - 1][idx2 - 1];
                if (word1[idx1 - 1] == word2[idx2 - 1]) {
                    dp[idx1][idx2] = replaceOperations;
                } else {
                    dp[idx1][idx2] = 1 + min(min(insertOperations, deleteOperations), replaceOperations);
                }
            }
        }
        retVal = dp[word1Size][word2Size];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word1;
        string word2;
    };
    vector<subject> testData{{"horse", "ros"}, {"intention", "execution"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word1 = "horse", word2 = "ros"
     *  Output: 3
     *
     *  Input: word1 = "intention", word2 = "execution"
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word1 = \"" << testData[i].word1 << "\", word2 = \"" << testData[i].word2 << "\"\n";

        answer = cSolution.minDistance(testData[i].word1, testData[i].word2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
