#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isSet(int x, int bit) {
        bool retVal = x & (1 << bit);

        return retVal;
    }
    int setBit(int x, int bit) {
        int retVal = x | (1 << bit);

        return retVal;
    }
    int unsetBit(int x, int bit) {
        int retVal = x & (~(1 << bit));

        return retVal;
    }

   public:
    int minimizeXor(int num1, int num2) {
        int retVal = num1;

        int targetSetBitsCount = __builtin_popcount(num2);
        int setBitsCount = __builtin_popcount(retVal);
        int currentBit = 0;

        while (setBitsCount < targetSetBitsCount) {
            if (isSet(retVal, currentBit) == false) {
                retVal = setBit(retVal, currentBit);
                setBitsCount++;
            }
            currentBit++;
        }

        while (setBitsCount > targetSetBitsCount) {
            if (isSet(retVal, currentBit) == true) {
                retVal = unsetBit(retVal, currentBit);
                setBitsCount--;
            }
            currentBit++;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int num1;
        int num2;
    };
    vector<subject> testData{{3, 5}, {1, 12}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num1 = 3, num2 = 5
     *  Output: 3
     *
     *  Input: num1 = 1, num2 = 12
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num1 = " << testData[i].num1 << ", num2 = " << testData[i].num2 << "\n";

        answer = cSolution.minimizeXor(testData[i].num1, testData[i].num2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
