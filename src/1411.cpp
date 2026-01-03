#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int numOfWays(int n) {
        int retVal = 0;

        long long fi0 = 6;
        long long fi1 = 6;
        for (int i = 2; i <= n; ++i) {
            long long fi0New = (2 * fi0 + 2 * fi1) % MODULO;
            long long fi1New = (2 * fi0 + 3 * fi1) % MODULO;
            fi0 = fi0New;
            fi1 = fi1New;
        }
        retVal = (fi0 + fi1) % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {5000}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 12
     *
     *  Input: n = 5000
     *  Output: 30228214
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.numOfWays(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
