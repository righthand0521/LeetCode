#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool dfs(int maxChoosableInteger, int usedNumbers, int desiredTotal, int currentTotal,
             unordered_map<int, bool>& memo) {
        bool retVal = false;

        if (memo.count(usedNumbers)) {
            retVal = memo[usedNumbers];
            return retVal;
        }

        for (int i = 0; i < maxChoosableInteger; i++) {
            if (((usedNumbers >> i) & 1) != 0) {
                continue;
            }

            if (i + 1 + currentTotal >= desiredTotal) {
                retVal = true;
                break;
            }

            if (dfs(maxChoosableInteger, usedNumbers | (1 << i), desiredTotal, currentTotal + i + 1, memo) == false) {
                retVal = true;
                break;
            }
        }
        memo[usedNumbers] = retVal;

        return retVal;
    }
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        bool retVal = false;

        if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal) {
            return retVal;
        }

        unordered_map<int, bool> memo;
        retVal = dfs(maxChoosableInteger, 0, desiredTotal, 0, memo);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int maxChoosableInteger;
        int desiredTotal;
    };
    vector<subject> testData{{10, 11}, {10, 0}, {10, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: maxChoosableInteger = 10, desiredTotal = 11
     *  Output: false
     *
     *  Input: maxChoosableInteger = 10, desiredTotal = 0
     *  Output: true
     *
     *  Input: maxChoosableInteger = 10, desiredTotal = 1
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: maxChoosableInteger = " << testData[i].maxChoosableInteger
             << ", desiredTotal = " << testData[i].desiredTotal << "\n";

        answer = cSolution.canIWin(testData[i].maxChoosableInteger, testData[i].desiredTotal);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
