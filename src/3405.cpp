#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static const int maxNumber = 1e5;  // // 1 <= n <= 10^5, 1 <= m <= 10^5
vector<long long> factory(maxNumber);
vector<long long> incertFactory(maxNumber);
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

    long long qpower(long long x, int n) {
        long long retVal = 1;

        while (n) {
            if (n & 1) {
                retVal = retVal * x % MODULO;
            }
            x = x * x % MODULO;
            n >>= 1;
        }

        return retVal;
    }
    long long combine(int n, int m) {
        long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

        return retVal;
    }

   public:
    int countGoodArrays(int n, int m, int k) {
        int retVal = 0;

        if (factory[0] == 0) {
            factory[0] = 1;
            for (int i = 1; i < maxNumber; i++) {
                factory[i] = factory[i - 1] * i % MODULO;
            }

            incertFactory[maxNumber - 1] = qpower(factory[maxNumber - 1], MODULO - 2);
            for (int i = maxNumber - 1; i; i--) {
                incertFactory[i - 1] = incertFactory[i] * i % MODULO;
            }
        }
        retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
        int k;
    };
    vector<subject> testData{{3, 2, 1}, {4, 2, 2}, {5, 2, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, m = 2, k = 1
     *  Output: 4
     *
     *  Input: n = 4, m = 2, k = 2
     *  Output: 6
     *
     *  Input: n = 5, m = 2, k = 0
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << ", k = " << testData[i].k << "\n";

        answer = cSolution.countGoodArrays(testData[i].n, testData[i].m, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
