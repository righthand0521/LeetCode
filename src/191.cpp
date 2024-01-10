#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int hammingWeight(uint32_t n) {
        int retVal = 0;

        while (n > 0) {
            retVal += (n & 1);
            n >>= 1;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string n;
    };
    vector<subject> testData{{"00000000000000000000000000001011"},
                             {"00000000000000000000000010000000"},
                             {"11111111111111111111111111111101"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 00000000000000000000000000001011
     *  Output: 3
     *
     *  Input: n = 00000000000000000000000010000000
     *  Output: 1
     *
     *  Input: n = 11111111111111111111111111111101
     *  Output: 31
     */

    Solution cSolution;
    uint32_t n;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        n = stoul(testData[i].n, NULL, 2);
        answer = cSolution.hammingWeight(n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
