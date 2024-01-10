#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int totalMoney(int n) {
        int retVal = 0;

        int weeks = n / 7;
        int days = n % 7;

        int firstWeek = (1 + 7) * 7 / 2;
        int lastWeek = firstWeek + (weeks - 1) * 7;
        int weeksMoney = (firstWeek + lastWeek) * weeks / 2;

        int dyasMoney = 0;
        int monday = 1 + weeks;
        for (int i = 0; i < days; ++i) {
            dyasMoney += (monday + i);
        }

        retVal = weeksMoney + dyasMoney;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{4}, {10}, {20}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4
     *  Output: 10
     *
     *  Input: n = 10
     *  Output: 37
     *
     *  Input: n = 20
     *  Output: 96
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.totalMoney(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
