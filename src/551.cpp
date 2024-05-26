#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkRecord(string s) {
        bool retVal = true;

        int late = 0;
        int absent = 0;
        for (char c : s) {
            if (c == 'A') {
                late = 0;
                absent++;
                if (absent >= 2) {
                    retVal = false;
                    break;
                }
            } else if (c == 'L') {
                late++;
                if (late >= 3) {
                    retVal = false;
                    break;
                }
            } else {
                late = 0;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"PPALLP"}, {"PPALLL"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "PPALLP"
     *  Output: true
     *
     *  Input: s = "PPALLL"
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.checkRecord(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
