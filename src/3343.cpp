#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)

   public:
    int countBalancedPermutations(string num) {
        int retVal = 0;

        int numSize = num.size();

        int tot = 0;
        vector<int> cnt(10);
        for (char ch : num) {
            int d = ch - '0';
            cnt[d]++;
            tot += d;
        }
        if (tot % 2 != 0) {
            return retVal;
        }

        int target = tot / 2;
        int maxOdd = (numSize + 1) / 2;

        vector<vector<long long>> dp(target + 1, vector<long long>(maxOdd + 1));
        dp[0][0] = 1;

        vector<vector<long long>> comb(maxOdd + 1, vector<long long>(maxOdd + 1));
        for (int i = 0; i <= maxOdd; i++) {
            comb[i][i] = 1;
            comb[i][0] = 1;
            for (int j = 1; j < i; j++) {
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODULO;
            }
        }

        int psum = 0, totSum = 0;
        for (int i = 0; i <= 9; i++) {
            psum += cnt[i];        // Sum of the number of the first i digits
            totSum += i * cnt[i];  // Sum of the first i numbers

            int oddCntStart = min(psum, maxOdd);
            int oddCntEnd = max(0, psum - (numSize - maxOdd));
            for (int oddCnt = oddCntStart; oddCnt >= oddCntEnd; oddCnt--) {
                int evenCnt = psum - oddCnt;  // The number of bits that need to be filled in even numbered positions

                int currStart = min(totSum, target);
                int currEnd = max(0, totSum - target);
                for (int curr = currStart; curr >= currEnd; curr--) {
                    long long res = 0;

                    int jStart = max(0, cnt[i] - evenCnt);
                    int jEnd = min(cnt[i], oddCnt);
                    for (int j = jStart; j <= jEnd && i * j <= curr; j++) {
                        // The current digit is filled with j positions at odd positions,
                        // and cnt[i] - j positions at even positions
                        long long ways = comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MODULO;
                        res = (res + ways * dp[curr - i * j][oddCnt - j] % MODULO) % MODULO;
                    }

                    dp[curr][oddCnt] = res % MODULO;
                }
            }
        }
        retVal = dp[target][maxOdd];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num;
    };
    vector<subject> testData{{"123"}, {"112"}, {"12345"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = "123"
     *  Output: 2
     *
     *  Input: num = "112"
     *  Output: 1
     *
     *  Input: num = "12345"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].num << "\"\n";

        answer = cSolution.countBalancedPermutations(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
