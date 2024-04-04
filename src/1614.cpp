#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDepth(string s) {
        int retVal = 0;

        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
            }
            retVal = max(retVal, count);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"(1+(2*3)+((8)/4))+1"}, {"(1)+((2))+(((3)))"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "(1+(2*3)+((8)/4))+1"
     *  Output: 3
     *
     *  Input: s = "(1)+((2))+(((3)))"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxDepth(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
