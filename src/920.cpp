#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numMusicPlaylists(int n, int goal, int k) {
        int retVal = 0;

        // the number of possible playlists of length goal containing exactly n unique songs
        vector<vector<long>> dp(goal + 1, vector<long>(n + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i < (goal + 1); ++i) {
            int uniqueSongs = min(i, n);
            for (int j = 1; j < (uniqueSongs + 1); ++j) {
                // The i-th song is a new song
                dp[i][j] = dp[i - 1][j - 1] * (n - j + 1) % MODULO;
                // The i-th song is a song we have played before
                if (j > k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - k)) % MODULO;
                }
            }
        }

        retVal = dp[goal][n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int goal;
        int k;
    };
    vector<subject> testData{{3, 3, 1}, {2, 3, 0}, {2, 3, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, goal = 3, k = 1
     *  Output: 6
     *
     *  Input: n = 2, goal = 3, k = 0
     *  Output: 6
     *
     *  Input: n = 2, goal = 3, k = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", goal = " << testData[i].goal << ", k = " << testData[i].k << "\n";

        answer = cSolution.numMusicPlaylists(testData[i].n, testData[i].goal, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
