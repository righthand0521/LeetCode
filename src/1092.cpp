#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string shortestCommonSupersequence(string str1, string str2) {
        string retVal = "";

        int str1Size = str1.length();
        int str2Size = str2.length();

        // Initialize the base cases
        vector<vector<int>> dp(str1Size + 1, vector<int>(str2Size + 1, 0));
        // When str2 is empty, the supersequence is str1 itself (length = row index)
        for (int row = 0; row <= str1Size; row++) {
            dp[row][0] = row;
        }
        // When str1 is empty, the supersequence is str2 itself (length = col index)
        for (int col = 0; col <= str2Size; col++) {
            dp[0][col] = col;
        }

        for (int row = 1; row <= str1Size; row++) {
            for (int col = 1; col <= str2Size; col++) {
                if (str1[row - 1] == str2[col - 1]) {  // If characters match, inherit the length from the diagonal + 1
                    dp[row][col] = dp[row - 1][col - 1] + 1;
                } else {  // If characters do not match, take the minimum length option + 1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
                }
            }
        }

        int row = str1Size;
        int col = str2Size;
        while (row > 0 && col > 0) {
            if (str1[row - 1] == str2[col - 1]) {  // If characters match, take it from diagonal
                retVal += str1[row - 1];
                row--;
                col--;
            } else if (dp[row - 1][col] < dp[row][col - 1]) {  // If str1’s character is part of the retVal, move up
                retVal += str1[row - 1];
                row--;
            } else {  // If str2’s character is part of the retVal, move left
                retVal += str2[col - 1];
                col--;
            }
        }

        // Append any remaining characters If there are leftover characters in str1
        while (row > 0) {
            retVal += str1[row - 1];
            row--;
        }
        // If there are leftover characters in str2
        while (col > 0) {
            retVal += str2[col - 1];
            col--;
        }
        // Reverse the built sequence to get the correct order
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string str1;
        string str2;
    };
    vector<subject> testData{{"abac", "cab"}, {"aaaaaaaa", "aaaaaaaa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: str1 = "abac", str2 = "cab"
     *  Output: "cabac"
     *
     *  Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
     *  Output: "aaaaaaaa"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: str1 = \"" << testData[i].str1 << "\"";
        cout << ", str2 = \"" << testData[i].str2 << "\"\n";

        answer = cSolution.shortestCommonSupersequence(testData[i].str1, testData[i].str2);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
