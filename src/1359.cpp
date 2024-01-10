#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countOrders(int n) {
        int retVal = 0;

        // https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/solutions/516968/java-c-python-easy-and-concise/
        long combinatorics = 1;
        for (int i = 1; i <= n; ++i) {
            combinatorics = combinatorics * ((i * 2 - 1) * i) % MODULO;
        }
        retVal = combinatorics;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {2}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 2
     *  Output: 6
     *
     *  Input: n = 3
     *  Output: 90
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countOrders(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
