#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findComplement(int num) {
        int retVal = num;

        int i = 31;
        while ((retVal & ((uint32_t)1 << i)) == 0) {
            i--;
        }

        while (i >= 0) {
            retVal ^= (1 << i--);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{5}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 5
     *  Output: 2
     *
     *  Input: num = 1
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.findComplement(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
