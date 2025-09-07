#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sumZero(int n) {
        vector<int> retVal(n, 0);

        for (int i = 0; i < n / 2; i++) {
            retVal[i] = (i + 1);
            retVal[n - 1 - i] = -(i + 1);
        }
        if (n % 2 == 1) {
            retVal[n / 2] = 0;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {3}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: [-7,-1,1,3,4]
     *
     *  Input: n = 3
     *  Output: [-1,0,1]
     *
     *  Input: n = 1
     *  Output: [0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.sumZero(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
