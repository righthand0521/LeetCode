#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // To count how many numbers exist between prefix1 and prefix2
    int countSteps(int n, long prefix1, long prefix2) {
        int retVal = 0;

        while (prefix1 <= n) {
            retVal += min((long)(n + 1), prefix2) - prefix1;
            prefix1 *= 10;
            prefix2 *= 10;
        }

        return retVal;
    }

   public:
    int findKthNumber(int n, int k) {
        int retVal = 1;

        k--;
        while (k > 0) {
            int step = countSteps(n, retVal, retVal + 1);

            // If the steps are less than or equal to k, we skip this prefix's subtree
            if (step <= k) {
                // Move to the next prefix and decrease k by the number of steps we skip
                retVal++;
                k -= step;
            } else {
                // Move to the next level of the tree and decrement k by 1
                retVal *= 10;
                k--;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{13, 2}, {1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 13, k = 2
     *  Output: 10
     *
     *  Input: n = 1, k = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.findKthNumber(testData[i].n, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
