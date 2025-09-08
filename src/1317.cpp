#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getNoZeroIntegers(int n) {
        vector<int> retVal(2, 0);

        for (int a = 1; a < n; ++a) {
            int b = n - a;
            if ((to_string(a).find('0') == string::npos) && (to_string(b).find('0') == string::npos)) {
                retVal[0] = a;
                retVal[1] = b;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {11}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: [1,1]
     *
     *  Input: n = 11
     *  Output: [2,9]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.getNoZeroIntegers(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
