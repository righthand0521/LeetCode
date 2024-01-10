#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#if (1)  // pre-defined API
int pick;
int guess(int num) {
    int retVal = 0;

    if (num > pick) {
        retVal = -1;
    } else if (num < pick) {
        retVal = 1;
    }

    return retVal;
}
#endif
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
class Solution {
   public:
    int guessNumber(int n) {
        int retVal = 0;

        int left = 1;
        int right = n;
        while (left <= right) {
            int middle = left + ((right - left) / 2);

            int ret = guess(middle);
            if (ret == 0) {
                retVal = middle;
                break;
            } else if (ret == -1) {
                right = middle - 1;
            } else if (ret == 1) {
                left = middle + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int pick;
    };
    vector<subject> testData{{10, 6}, {1, 1}, {2, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10, pick = 6
     *  Output: 6
     *
     *  Input: n = 1, pick = 1
     *  Output: 1
     *
     *  Input: n = 2, pick = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", pick = " << testData[i].pick << "\n";

        pick = testData[i].pick;
        answer = cSolution.guessNumber(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
