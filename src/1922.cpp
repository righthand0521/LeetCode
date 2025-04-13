#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   private:
    long long quickmul(int x, long long y) {
        long long retVal = 1;

        long long mul = x;
        while (y > 0) {
            if (y % 2 == 1) {
                retVal = (retVal * mul) % MODULO;
            }
            mul = (mul * mul) % MODULO;
            y /= 2;
        }

        return retVal;
    }

   public:
    int countGoodNumbers(long long n) {
        int retVal = 0;

        retVal = (int)(quickmul(5, (n + 1) / 2) * quickmul(4, n / 2) % MODULO);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        long long n;
    };
    vector<subject> testData{{1}, {4}, {50}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 5
     *
     *  Input: n = 4
     *  Output: 400
     *
     *  Input: n = 50
     *  Output: 564908303
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countGoodNumbers(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
