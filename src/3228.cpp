#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxOperations(string s) {
        int retVal = 0;

        int sSize = s.size();

        int countOne = 0;
        int i = 0;
        while (i < sSize) {
            if (s[i] == '0') {
                while (((i + 1) < sSize) && (s[i + 1] == '0')) {
                    i++;
                }
                retVal += countOne;
            } else {
                countOne++;
            }

            i++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"1001101"}, {"00111"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1001101"
     *  Output: 4
     *
     *  Input: s = "00111"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxOperations(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
