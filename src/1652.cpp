#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> decrypt(vector<int>& code, int k) {
        vector<int> retVal;

        int codeSize = code.size();

        retVal.assign(codeSize, 0);
        if (k == 0) {
            return retVal;
        }

        int start = 1;
        int end = k;
        if (k < 0) {  // If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k);
            end = codeSize - 1;
        }

        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += code[i];
        }

        // Scan through the code array as i moving to the right, update the window sum.
        for (int i = 0; i < codeSize; i++) {
            retVal[i] = sum;
            sum -= code[start % codeSize];
            sum += code[(end + 1) % codeSize];
            start++;
            end++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> code;
        int k;
    };
    vector<subject> testData{{{5, 7, 1, 4}, 3}, {{1, 2, 3, 4}, 0}, {{2, 4, 9, 3}, -2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: code = [5,7,1,4], k = 3
     *  Output: [12,10,16,13]
     *
     *  Input: code = [1,2,3,4], k = 0
     *  Output: [0,0,0,0]
     *
     *  Input: code = [2,4,9,3], k = -2
     *  Output: [12,5,6,13]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: code = [";
        for (long unsigned int j = 0; j < testData[i].code.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].code[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.decrypt(testData[i].code, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
