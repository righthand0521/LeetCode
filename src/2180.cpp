#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MATH (1)
#define BRUTE_FORCE (1)
   public:
    int countEven(int num) {
        int retVal = 0;

#if (MATH)
        cout << "MATH\n";

        /* Math
         *  nums = xyz, sum of digits = x + y + z.
         *  if x + y + z is even, the even digit sums is nums / 2.
         *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
         */
        int sum = 0;
        int tmp = num;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }

        if (sum % 2 == 0) {
            retVal = num / 2;
        } else {
            retVal = (num - 1) / 2;
        }
#elif (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        for (int i = 2; i <= num; ++i) {
            int sum = 0;
            int tmp = i;
            while (tmp > 0) {
                sum += (tmp % 10);
                tmp /= 10;
            }
            if (sum % 2 == 0) {
                ++retVal;
            }
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{4}, {30}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.countEven(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
