#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minLength(string s) {
        int retVal = 0;

        vector<char> stack;
        for (char c : s) {
            if (stack.empty() == true) {
                stack.push_back(c);
            } else if ((c == 'B') && (stack.back() == 'A')) {
                stack.pop_back();
            } else if ((c == 'D') && (stack.back() == 'C')) {
                stack.pop_back();
            } else {
                stack.push_back(c);
            }
        }
        retVal = stack.size();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"ABFCACDB"}, {"ACBBD"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ABFCACDB"
     *  Output: 2
     *
     *  Input: s = "ACBBD"
     *  Output: 5
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minLength(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
