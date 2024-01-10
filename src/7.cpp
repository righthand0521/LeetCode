#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int reverse(int x) {
        int retVal = 0;

        long long reverseSum = 0;
        while (x != 0) {
            reverseSum = (reverseSum * 10) + (x % 10);
            x /= 10;
        }

        // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
        // then return 0.
        if ((reverseSum < numeric_limits<int>::max()) && (reverseSum > numeric_limits<int>::min())) {
            retVal = reverseSum;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int x;
    };
    vector<subject> testData{{123}, {-123}, {120}, {numeric_limits<int>::max()}, {numeric_limits<int>::min()}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: x = 123
     *  Output: 321
     *
     *  Input: x = -123
     *  Output: -321
     *
     *  Input: x = 120
     *  Output: 21
     *
     *  Input: x = 2147483647
     *  Output: 0
     *
     *  Input: x = -2147483648
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].x << "\n";

        answer = cSolution.reverse(testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
