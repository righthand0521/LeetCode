#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int makeTheIntegerZero(int num1, int num2) {
        int retVal = -1;

        int k = 1;
        while (true) {
            long long x = num1 - static_cast<long long>(num2) * k;
            if (x < k) {
                break;
            } else if (k >= __builtin_popcountll(x)) {
                retVal = k;
                break;
            }
            k++;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int num1;
        int num2;
    };
    vector<subject> testData{{3, -2}, {5, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num1 = 3, num2 = -2
     *  Output: 3
     *
     *  Input: num1 = 5, num2 = 7
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num1 = " << testData[i].num1 << ", num2 = " << testData[i].num2 << "\n";

        answer = cSolution.makeTheIntegerZero(testData[i].num1, testData[i].num2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
