#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool judgeSquareSum(int c) {
        bool retVal = false;

        long left = 0;
        long right = (int)sqrt(c);
        while (left <= right) {
            long sum = (left * left) + (right * right);
            if (sum == c) {
                retVal = true;
                break;
            } else if (sum > c) {
                right--;
            } else {
                left++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int c;
    };
    vector<subject> testData{{5}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: c = 5
     *  Output: true
     *
     *  Input: c = 3
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: c = " << testData[i].c << "\n";

        answer = cSolution.judgeSquareSum(testData[i].c);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
