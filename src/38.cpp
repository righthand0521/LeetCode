#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string countAndSay(int n) {
        string retVal = "1";

        for (int i = 2; i <= n; ++i) {
            string curr = "";
            int start = 0;
            int pos = 0;
            int retValSize = retVal.size();
            while (pos < retValSize) {
                while ((pos < retValSize) && (retVal[pos] == retVal[start])) {
                    pos++;
                }
                curr += to_string(pos - start) + retVal[start];
                start = pos;
            }
            retVal = curr;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{4}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4
     *  Output: "1211"
     *
     *  Input: n = 1
     *  Output: "1"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countAndSay(testData[i].n);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
