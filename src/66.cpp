#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> retVal = digits;

        int digitsSize = digits.size();
        for (int i = digitsSize - 1; i >= 0; --i) {
            retVal[i] += 1;
            if (retVal[i] != 10) {
                return retVal;
            }
            retVal[i] = 0;
        }
        retVal.resize(digitsSize + 1);
        retVal[0] = 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> digits;
    };
    vector<subject> testData{{{1, 2, 3}}, {{4, 3, 2, 1}}, {{9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: digits = [1,2,3]
     *  Output: [1,2,4]
     *
     *  Input: digits = [4,3,2,1]
     *  Output: [4,3,2,2]
     *
     *  Input: digits = [9]
     *  Output: [1,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: digits = [";
        for (long unsigned int j = 0; j < testData[i].digits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].digits[j];
        }
        cout << "]\n";

        answer = cSolution.plusOne(testData[i].digits);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
