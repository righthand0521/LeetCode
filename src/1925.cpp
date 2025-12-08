#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countTriples(int n) {
        int retVal = 0;

        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                int c = int(sqrt(a * a + b * b + 1.0));
                if ((c <= n) && (c * c == a * a + b * b)) {
                    ++retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: 2
     *
     *  Input: n = 10
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countTriples(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
