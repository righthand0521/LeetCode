#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    long counter(int n) {
        long retVal = 0;

        for (; n; n /= 10) {
            retVal += pow(10, n % 10);
        }

        return retVal;
    }

   public:
    bool reorderedPowerOf2(int n) {
        bool retVal = false;

        long c = counter(n);
        for (int i = 0; i < 32; i++) {
            if (counter(1 << i) == c) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: true
     *
     *  Input: n = 10
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.reorderedPowerOf2(testData[i].n);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
