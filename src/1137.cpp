#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define TRIBONACCI_0 (0)
#define TRIBONACCI_1 (1)
#define TRIBONACCI_2 (1)
   public:
    int tribonacci(int n) {
        int retVal = 0;

        switch (n) {
            case 0:
                retVal = TRIBONACCI_0;
                break;

            case 1:
                retVal = TRIBONACCI_1;
                break;

            case 2:
                retVal = TRIBONACCI_2;
                break;

            default:
                vector<int> dp(n + 1, 0);
                dp[0] = TRIBONACCI_0;
                dp[1] = TRIBONACCI_1;
                dp[2] = TRIBONACCI_2;
                for (int i = 3; i <= n; ++i) {
                    dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
                }
                retVal = dp[n];
                break;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{4}, {25}, {5}, {6}, {7}, {8}, {9}, {0}, {1}, {2}, {37}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4
     *  Output: 4
     *
     *  Input: n = 25
     *  Output: 1389537
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.tribonacci(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
