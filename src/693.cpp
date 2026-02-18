#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool hasAlternatingBits(int n) {
        bool retVal = false;

        long a = n ^ (n >> 1);
        if ((a & (a + 1)) == 0) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {7}, {11}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: true
     *
     *  Input: n = 7
     *  Output: false
     *
     *  Input: n = 11
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.hasAlternatingBits(testData[i].n);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
