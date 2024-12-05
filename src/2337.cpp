#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canChange(string start, string target) {
        bool retVal = true;

        int startSize = start.size();
        int startIndex = 0;
        int targetIndex = 0;
        while ((startIndex < startSize) || (targetIndex < startSize)) {
            // Skip underscores in start
            while ((startIndex < startSize) && (start[startIndex] == '_')) {
                startIndex++;
            }
            // Skip underscores in target
            while ((targetIndex < startSize) && (target[targetIndex] == '_')) {
                targetIndex++;
            }

            // If one string is exhausted, both should be exhausted
            if ((startIndex == startSize) || (targetIndex == startSize)) {
                retVal = (startIndex == startSize) && (targetIndex == startSize);
                break;
            }

            // Check if the pieces match and follow movement rules
            if (start[startIndex] != target[targetIndex]) {
                retVal = false;
                break;
            } else if ((start[startIndex] == 'L') && (startIndex < targetIndex)) {
                retVal = false;
                break;
            } else if ((start[startIndex] == 'R') && (startIndex > targetIndex)) {
                retVal = false;
                break;
            }

            startIndex++;
            targetIndex++;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string start;
        string target;
    };
    vector<subject> testData{{"_L__R__R_", "L______RR"}, {"R_L_", "__LR"}, {"_R", "R_"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: start = "_L__R__R_", target = "L______RR"
     *  Output: true
     *
     *  Input: start = "R_L_", target = "__LR"
     *  Output: false
     *
     *  Input: start = "_R", target = "R_"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: start = \"" << testData[i].start << "\"";
        cout << ", target = \"" << testData[i].target << "\"\n";

        answer = cSolution.canChange(testData[i].start, testData[i].target);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
