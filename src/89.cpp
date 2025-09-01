#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> grayCode(int n) {
        vector<int> retVal;

        int returnSize = (1 << n);
        retVal = vector<int>(returnSize);
        for (int i = 0; i < returnSize; i++) {
            retVal[i] = (i >> 1) ^ i;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {1}, {3}, {4}, {5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: [0,1,3,2]
     *
     *  Input: n = 1
     *  Output: [0,1]
     *
     *  Input: n = 3
     *  Output: [0,1,3,2,6,7,5,4]
     *
     *  Input: n = 4
     *  Output: [0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8]
     *
     *  Input: n = 5
     *  Output: [0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8,24,25,27,26,30,31,29,28,20,21,23,22,18,19,17,16]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.grayCode(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
