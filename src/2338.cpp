#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MODULO (int)(1e9 + 7)
#define MAX_N (int)(1e4 + 10)
#define MAX_P (15)      // There are up to 15 prime factors
int sieve[MAX_N];       // Minimum prime factor
vector<int> ps[MAX_N];  // List of prime factor counts
int c[MAX_N + MAX_P][MAX_P + 1];
class Solution {
   public:
    Solution() {
        if (c[0][0]) {
            return;
        }

        for (int i = 2; i < MAX_N; i++) {
            if (sieve[i] != 0) {
                continue;
            }
            for (int j = i; j < MAX_N; j += i) {
                sieve[j] = i;
            }
        }

        for (int i = 2; i < MAX_N; i++) {
            int x = i;
            while (x > 1) {
                int p = sieve[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                ps[i].push_back(cnt);
            }
        }

        c[0][0] = 1;
        for (int i = 1; i < MAX_N + MAX_P; i++) {
            c[i][0] = 1;
            for (int j = 1; j <= min(i, MAX_P); j++) {
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODULO;
            }
        }
    }
    int idealArrays(int n, int maxValue) {
        int retVal = 0;

        long long ans = 0;
        for (int x = 1; x <= maxValue; x++) {
            long long mul = 1;
            for (int p : ps[x]) {
                mul = mul * c[n + p - 1][p] % MODULO;
            }
            ans = (ans + mul) % MODULO;
        }
        retVal = ans;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int maxValue;
    };
    vector<subject> testData{{2, 5}, {5, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, maxValue = 5
     *  Output: 10
     *
     *  Input: n = 5, maxValue = 3
     *  Output: 11
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", maxValue = " << testData[i].maxValue << "\n";

        answer = cSolution.idealArrays(testData[i].n, testData[i].maxValue);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
