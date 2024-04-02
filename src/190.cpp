#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t retVal = 0;

        for (int i = 0; i < 32; ++i) {
            retVal = (retVal << 1) | (n & 0x1);
            n >>= 1;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string n;
    };
    vector<subject> testData{{"00000010100101000001111010011100"}, {"11111111111111111111111111111101"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 00000010100101000001111010011100
     *  Output:    964176192 (00111001011110000010100101000000)
     *
     *  Input: n = 11111111111111111111111111111101
     *  Output:   3221225471 (10111111111111111111111111111111)
     */

    Solution cSolution;
    uint32_t n;
    uint32_t answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        n = stoul(testData[i].n, NULL, 2);
        answer = cSolution.reverseBits(n);
        cout << "Output: " << answer << " (" << bitset<32>(answer) << ")\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
