#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define REVERSE (1)
#define MATH (1)
   public:
    int alternateDigitSum(int n) {
        int retVal = 0;

        vector<int> nums;
#if (REVERSE)
        cout << "REVERSE\n";

        while (n > 0) {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());

        int sign = 1;
        for (auto num : nums) {
            retVal += (sign * num);
            sign *= (-1);
        }
#elif (MATH)
        cout << "MATH\n";

        /* Alternating Digit Sum
         *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
         *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
         */
        int sign = -1;
        while (n > 0) {
            sign *= (-1);
            retVal += (sign * (n % 10));
            n /= 10;
        }
        retVal *= sign;
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{521}, {111}, {886996}, {10}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.alternateDigitSum(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
