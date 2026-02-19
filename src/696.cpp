#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countBinarySubstrings(string s) {
        int retVal = 0;

        int sSize = s.size();

        int current = 1;
        int previous = 0;
        for (int i = 1; i < sSize; ++i) {
            if (s[i] != s[i - 1]) {
                retVal += min(current, previous);
                previous = current;
                current = 1;
            } else {
                ++current;
            }
        }
        retVal += min(current, previous);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"00110011"}, {"10101"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "00110011"
     *  Output: 6
     *
     *  Input: s = "10101"
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.countBinarySubstrings(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
