#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    char findKthBit(int n, int k) {
        int retVal = '0';

        if (n == 1) {
            return retVal;
        }

        int length = 1 << n;
        if (k < length / 2) {
            retVal = findKthBit(n - 1, k);
        } else if (k == length / 2) {
            retVal = '1';
        } else {
            char correspondingBit = findKthBit(n - 1, length - k);
            retVal = (correspondingBit == '0') ? '1' : '0';
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{3, 1}, {4, 11}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, k = 1
     *  Output: "0"
     *
     *  Input: n = 4, k = 11
     *  Output: "1"
     */

    Solution cSolution;
    char answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.findKthBit(testData[i].n, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
