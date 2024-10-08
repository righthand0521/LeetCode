#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSwaps(string s) {
        int retVal = 0;

        int stackSize = 0;
        for (char c : s) {
            if (c == '[') {
                // If character is opening bracket, increment the stack size.
                stackSize++;
            } else if (stackSize > 0) {
                // If the character is closing bracket, and we have an opening bracket, decrease the stack size.
                stackSize--;
            }
        }
        retVal = (stackSize + 1) / 2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"][]["}, {"]]][[["}, {"[]"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "][]["
     *  Output: 1
     *
     *  Input: s = "]]][[["
     *  Output: 2
     *
     *  Input: s = "[]"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minSwaps(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
