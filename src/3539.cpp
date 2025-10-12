#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    const long long MODULO = 1e9 + 7;

    long long quickmul(long long x, long long y) {
        long long retVal = 1;

        long long current = x % MODULO;
        while (y) {
            if (y & 1) {
                retVal = retVal * current % MODULO;
            }
            y >>= 1;

            current = current * current % MODULO;
        }

        return retVal;
    };

   public:
    int magicalSum(int m, int k, vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<long long> fac(m + 1, 1);
        for (int i = 1; i <= m; i++) {
            fac[i] = fac[i - 1] * i % MODULO;
        }

        vector<long long> ifac(m + 1, 1);
        for (int i = 2; i <= m; i++) {
            ifac[i] = quickmul(i, MODULO - 2);
        }
        for (int i = 2; i <= m; i++) {
            ifac[i] = ifac[i - 1] * ifac[i] % MODULO;
        }

        vector numsPower(numsSize, vector<long long>(m + 1, 1));
        for (int i = 0; i < numsSize; i++) {
            for (int j = 1; j <= m; j++) {
                numsPower[i][j] = numsPower[i][j - 1] * nums[i] % MODULO;
            }
        }

        vector f(numsSize, vector(m + 1, vector(m * 2 + 1, vector<long long>(k + 1, 0))));
        for (int j = 0; j <= m; j++) {
            f[0][j][j][0] = numsPower[0][j] * ifac[j] % MODULO;
        }
        for (int i = 0; i + 1 < numsSize; i++) {
            for (int j = 0; j <= m; j++) {
                for (int p = 0; p <= m * 2; p++) {
                    for (int q = 0; q <= k; q++) {
                        int q2 = p % 2 + q;
                        if (q2 > k) {
                            break;
                        }

                        for (int r = 0; r + j <= m; r++) {
                            int p2 = p / 2 + r;
                            f[i + 1][j + r][p2][q2] += f[i][j][p][q] * numsPower[i + 1][r] % MODULO * ifac[r] % MODULO;
                            f[i + 1][j + r][p2][q2] %= MODULO;
                        }
                    }
                }
            }
        }

        for (int p = 0; p <= m * 2; p++) {
            for (int q = 0; q <= k; q++) {
                if (__builtin_popcount(p) + q == k) {
                    retVal = (retVal + f[numsSize - 1][m][p][q] * fac[m] % MODULO) % MODULO;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int k;
        vector<int> nums;
    };
    vector<subject> testData{{5, 5, {1, 10, 100, 10000, 1000000}}, {2, 2, {5, 4, 3, 2, 1}}, {1, 1, {28}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
     *  Output: 991600007
     *
     *  Input: m = 2, k = 2, nums = [5,4,3,2,1]
     *  Output: 170
     *
     *  Input: m = 1, k = 1, nums = [28]
     *  Output: 28
     */

    Solution cSolution;
    long long answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", k = " << testData[i].k << ", nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.magicalSum(testData[i].m, testData[i].k, testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
