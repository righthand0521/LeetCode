#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string maximumOddBinaryNumber(string s) {
        string retVal = "";

        int count1 = 0;
        int count0 = 0;
        for (auto c : s) {
            if (c == '1') {
                count1++;
            } else {
                count0++;
            }
        }

        for (int i = 1; i < count1; ++i) {
            retVal += "1";
        }
        for (int i = 0; i < count0; ++i) {
            retVal += "0";
        }
        retVal += "1";

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"010"}, {"0101"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "010"
     *  Output: "001"
     *
     *  Input: s = "0101"
     *  Output: "1001"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.maximumOddBinaryNumber(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
