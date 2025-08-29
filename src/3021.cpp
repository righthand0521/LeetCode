#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long flowerGame(int n, int m) {
        long long retVal = (long long)m * n / 2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
    };
    vector<subject> testData{{3, 2}, {1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, m = 2
     *  Output: 3
     *
     *  Input: n = 1, m = 1
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << "\n";

        answer = cSolution.flowerGame(testData[i].n, testData[i].m);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
