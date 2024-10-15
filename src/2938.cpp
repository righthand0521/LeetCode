#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minimumSteps(string s) {
        long long retVal = 0;

        int sum = 0;
        for (char c : s) {
            if (c == '1') {
                sum++;
            } else {
                retVal += sum;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"101"}, {"100"}, {"0111"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "101"
     *  Output: 1
     *
     *  Input: s = "100"
     *  Output: 2
     *
     *  Input: s = "0111"
     *  Output: 0
     */

    Solution cSolution;
    long long answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minimumSteps(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
