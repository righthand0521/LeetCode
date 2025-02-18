#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    string smallestNumber(string pattern) {
        string retVal;

        stack<int> numStack;
        int patternSize = pattern.size();
        for (int index = 0; index <= patternSize; index++) {
            // Push the next number onto the stack
            numStack.push(index + 1);

            if ((index != patternSize) && (pattern[index] != 'I')) {
                continue;
            }

            // If 'I' is encountered or we reach the end, pop all stack elements
            while (numStack.empty() == false) {
                retVal += to_string(numStack.top());
                numStack.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string pattern;
    };
    vector<subject> testData{{"IIIDIDDD"}, {"DDD"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pattern = "IIIDIDDD"
     *  Output: "123549876"
     *
     *  Input: pattern = "DDD"
     *  Output: "4321"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pattern = \"" << testData[i].pattern << "\"\n";

        answer = cSolution.smallestNumber(testData[i].pattern);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
