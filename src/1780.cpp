#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkPowersOfThree(int n) {
        bool retVal = false;

        /*  可以將 n 轉換成 3 進位
         *  如果 n 的 3 進制表示中每一位均不為 2, 那麼答案為 True, 否則為 False.
         *  例如, 當 n = 12 時, 12 = 110, 滿足要求; 當 n = 21 時, 21 = 210, 不滿足要求.
         */
        while (n > 0) {
            if (n % 3 == 2) {  // Check if this power should be used twice
                return retVal;
            }
            n /= 3;  // Divide n by 3 to move to the next greater power
        }
        retVal = true;  // The ternary representation of n consists only of 0s and 1s

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{12}, {91}, {21}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 12
     *  Output: true
     *
     *  Input: n = 91
     *  Output: true
     *
     *  Input: n = 21
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.checkPowersOfThree(testData[i].n);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
