#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minChanges(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 1; i < sSize; i += 2) {
            if (s[i - 1] != s[i]) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"1001"}, {"10"}, {"0000"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1001"
     *  Output: 2
     *
     *  Input: s = "10"
     *  Output: 1
     *
     *  Input: s = "0000"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minChanges(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
