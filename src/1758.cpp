#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            if (s[i] != '0' + (i % 2)) {
                ++retVal;
            }
        }
        retVal = min(retVal, (sSize - retVal));

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"0100"}, {"10"}, {"1111"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "0100"
     *  Output: 1
     *
     *  Input: s = "10"
     *  Output: 0
     *
     *  Input: s = "1111"
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\n";

        answer = cSolution.minOperations(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
