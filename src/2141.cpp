#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long retVal = 0;

        long sumPower = 0;
        for (auto battery : batteries) {
            sumPower += battery;
        }

        long long left = 1;
        long long right = sumPower / n;
        while (left < right) {
            long long middle = right - (right - left) / 2;

            long long total = 0;
            for (long long battery : batteries) {
                total += min(battery, middle);
            }
            if (total >= (long long)(n * middle)) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> batteries;
    };
    vector<subject> testData{{2, {3, 3, 3}}, {2, {1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, batteries = [3,3,3]
     *  Output: 4
     *
     *  Input: n = 2, batteries = [1,1,1,1]
     *  Output: 2
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", batteries = [";
        for (long unsigned int j = 0; j < testData[i].batteries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].batteries[j];
        }
        cout << "]\n";

        answer = cSolution.maxRunTime(testData[i].n, testData[i].batteries);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
