#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> lexicalOrder(int n) {
        vector<int> retVal;

        int currentNumber = 1;
        for (int i = 0; i < n; ++i) {
            retVal.emplace_back(currentNumber);

            if (currentNumber * 10 <= n) {
                currentNumber *= 10;
                continue;
            }

            while ((currentNumber % 10) == 9 || (currentNumber >= n)) {
                currentNumber /= 10;
            }
            currentNumber += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{13}, {2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 13
     *  Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
     *
     *  Input: n = 2
     *  Output: [1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.lexicalOrder(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
