#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool CanPartition(int num, int target) {
        bool retVal = false;

        if ((target < 0) || (target > num)) {
            return retVal;
        } else if (num == target) {
            retVal = true;
            return retVal;
        }
        retVal = CanPartition(num / 10, target - num % 10);
        retVal = retVal || CanPartition(num / 100, target - num % 100);
        retVal = retVal || CanPartition(num / 1000, target - num % 1000);

        return retVal;
    }

   public:
    int punishmentNumber(int n) {
        int retVal = 0;

        for (int currentNum = 1; currentNum <= n; currentNum++) {
            int squareNum = currentNum * currentNum;
            if (CanPartition(squareNum, currentNum) == true) {
                retVal += squareNum;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{10}, {37}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10
     *  Output: 182
     *
     *  Input: n = 37
     *  Output: 1478
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.punishmentNumber(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
