#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSymmetricIntegers(int low, int high) {
        int retVal = 0;

        // 1 <= low <= high <= 10^4
        for (int num = low; num <= high; ++num) {
            if (num < 100) {
                if (num % 11 == 0) {
                    retVal++;
                }
            } else if ((1000 <= num) && (num < 10000)) {
                int left = num / 1000 + (num % 1000) / 100;
                int right = (num % 100) / 10 + num % 10;
                if (left == right) {
                    retVal++;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int low;
        int high;
    };
    vector<subject> testData{{1, 100}, {1200, 1230}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: low = 1, high = 100
     *  Output: 9
     *
     *  Input: low = 1200, high = 1230
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: low = " << testData[i].low << ", high = " << testData[i].high << "\n";

        answer = cSolution.countSymmetricIntegers(testData[i].low, testData[i].high);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
