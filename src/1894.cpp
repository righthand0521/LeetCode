#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int retVal = 0;

        long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= total;

        int chalkSize = chalk.size();
        for (int i = 0; i < chalkSize; ++i) {
            if (chalk[i] > k) {
                retVal = i;
                break;
            }
            k -= chalk[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> chalk;
        int k;
    };
    vector<subject> testData{{{5, 1, 5}, 22}, {{3, 4, 1, 2}, 25}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: chalk = [5,1,5], k = 22
     *  Output: 0
     *
     *  Input: chalk = [3,4,1,2], k = 25
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: chalk = [";
        for (long unsigned int j = 0; j < testData[i].chalk.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].chalk[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.chalkReplacer(testData[i].chalk, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
