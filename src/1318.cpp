#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minFlips(int a, int b, int c) {
        int retVal = 0;

        while ((a > 0) || (b > 0) || (c > 0)) {
            if (c & 1) {
                retVal += ((~((a & 1) | (b & 1))) & 1);
            } else {
                retVal += ((a & 1) + (b & 1));
            }

            a >>= 1;
            b >>= 1;
            c >>= 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int a;
        int b;
        int c;
    };
    vector<subject> testData{{2, 6, 5}, {4, 2, 7}, {1, 2, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: a = 2, b = 6, c = 5
     *  Output: 3
     *
     *  Input: a = 4, b = 2, c = 7
     *  Output: 1
     *
     *  Input: a = 1, b = 2, c = 3
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: a = " << testData[i].a << ", b = " << testData[i].b << ", c = " << testData[i].c << "\n";

        answer = cSolution.minFlips(testData[i].a, testData[i].b, testData[i].c);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
