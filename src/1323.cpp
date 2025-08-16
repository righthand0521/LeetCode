#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximum69Number(int num) {
        int retVal = num;

        int add = 0;
        int multiplier = 1;
        int mod;
        while (num > 0) {
            mod = num % 10;
            if (mod == 6) {
                add = 3 * multiplier;
            }

            num -= mod;
            num /= 10;
            multiplier *= 10;
        }
        retVal += add;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{9669}, {9996}, {9999}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 9669
     *  Output: 9969
     *
     *  Input: num = 9996
     *  Output: 9999
     *
     *  Input: num = 9999
     *  Output: 9999
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.maximum69Number(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
