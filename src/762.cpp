#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countPrimeSetBits(int left, int right) {
        int retVal = 0;

        auto isPrime = [](int n) -> bool {
            if (n < 2) {
                return false;
            }
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    return false;
                }
            }
            return true;
        };

        auto countBits = [](int n) -> int {
            int count = 0;
            while (n) {
                count += n & 1;
                n >>= 1;
            }
            return count;
        };

        for (int i = left; i <= right; ++i) {
            int setBits = countBits(i);
            if (isPrime(setBits)) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int left;
        int right;
    };
    vector<subject> testData{{6, 10}, {10, 15}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: left = 6, right = 10
     *  Output: 4
     *
     *  Input: left = 10, right = 15
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: left = " << testData[i].left << ", right = " << testData[i].right << "\n";

        answer = cSolution.countPrimeSetBits(testData[i].left, testData[i].right);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
