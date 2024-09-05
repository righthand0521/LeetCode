#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        vector<int> retVal;

        int rollsSize = rolls.size();
        int total = mean * (rollsSize + n);
        for (int roll : rolls) {
            total -= roll;
        }
        if ((total > (6 * n)) || (total < n)) {
            return retVal;
        }

        int average = total / n;
        int index = total % n;

        retVal.resize(n, average);
        for (int i = 0; i < index; ++i) {
            retVal[i] += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> rolls;
        int mean;
        int n;
    };
    vector<subject> testData{{{3, 2, 4, 3}, 4, 2}, {{1, 5, 6}, 3, 4}, {{1, 2, 3, 4}, 6, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rolls = [3,2,4,3], mean = 4, n = 2
     *  Output: [6,6]
     *
     *  Input: rolls = [1,5,6], mean = 3, n = 4
     *  Output: [2,3,2,2]
     *
     *  Input: rolls = [1,2,3,4], mean = 6, n = 4
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rolls = [";
        for (long unsigned int j = 0; j < testData[i].rolls.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].rolls[j];
        }
        cout << "], mean = " << testData[i].mean << ", n = " << testData[i].n << "\n";

        answer = cSolution.missingRolls(testData[i].rolls, testData[i].mean, testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
