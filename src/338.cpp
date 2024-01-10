#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> retVal(n + 1, 0);

        for (int i = 1; i < n + 1; ++i) {
#if (1)  // O(n)
            /* f[i] = f[i/2] + i%2
             *  retVal[000] = 0
             *  retVal[001] = retVal[00] + (1%2) = 0 + 1 = 1
             *  retVal[010] = retVal[01] + (2%2) = 1 + 0 = 1
             *  retVal[011] = retVal[01] + (3%2) = 1 + 1 = 2
             *  retVal[100] = retVal[10] + (4%2) = 1 + 0 = 1
             *  retVal[101] = retVal[10] + (5%2) = 1 + 1 = 2
             *  retVal[110] = retVal[11] + (6%2) = 2 + 0 = 2
             *  retVal[111] = retVal[11] + (7%2) = 2 + 1 = 3
             */
            retVal[i] = retVal[i >> 1] + (i & 1);
#else  // O(n log n)
            unsigned int tmp = i;
            while (tmp) {
                if (tmp & 1) {
                    retVal[i]++;
                }
                tmp >>= 1;
            }
#endif
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: [0,1,1]
     *
     *  Input: n = 5
     *  Output: [0,1,1,2,1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countBits(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
