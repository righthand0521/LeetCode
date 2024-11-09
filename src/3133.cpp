#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minEnd(int n, int x) {
        long long retVal = x;

        --n;  // Reducing n by 1 to exclude x from the iteration

        // Step 1: Iterate over each bit position with mask starting at 1 and shifting left
        long long mask;
        for (mask = 1; n > 0; mask <<= 1) {
            // Step 2: If the corresponding bit in x is 0
            if ((mask & x) == 0) {
                retVal |= ((n & 1) * mask);  // Set the bit in result based on the least significant bit of n
                n >>= 1;                     // Shift n to the right by 1 to process the next bit
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int x;
    };
    vector<subject> testData{{3, 4}, {2, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, x = 4
     *  Output: 6
     *
     *  Input: n = 2, x = 7
     *  Output: 15
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", x = " << testData[i].x << "\n";

        answer = cSolution.minEnd(testData[i].n, testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
