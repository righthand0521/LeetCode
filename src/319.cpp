#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int bulbSwitch(int n) {
        /*      1   2   3   4   5   6   7   8   9   10
         *    +---+
         *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
         *    +---+---+
         *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
         *    +-------+---+
         *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
         *    +-----------+---+
         *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
         *    +---------------+---+
         *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
         *    +-------------------+---+
         *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
         *    +-----------------------+---+
         *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
         *    +---------------------------+---+
         *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
         *    +-------------------------------+---+
         *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
         *    +-----------------------------------+---+
         * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
         *    +---------------------------------------+
         */
        int retVal = sqrt(n + 0.5);

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {0}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: 1
     *
     *  Input: n = 0
     *  Output: 0
     *
     *  Input: n = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.bulbSwitch(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
