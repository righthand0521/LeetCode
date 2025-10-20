#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int finalValueAfterOperations(vector<string>& operations) {
        int retVal = 0;

        for (const string& operation : operations) {
            // operations[i] will be either "++X", "X++", "--X", or "X--"
            if ((operation == "++X") || (operation == "X++")) {
                retVal++;
            } else {
                retVal--;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> operations;
    };
    vector<subject> testData{{{"--X", "X++", "X++"}}, {{"++X", "++X", "X++"}}, {{"X++", "++X", "--X", "X--"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: operations = ["--X","X++","X++"]
     *  Output: 1
     *
     *  Input: operations = ["++X","++X","X++"]
     *  Output: 3
     *
     *  Input: operations = ["X++","++X","--X","X--"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: operations = [";
        for (long unsigned int j = 0; j < testData[i].operations.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].operations[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.finalValueAfterOperations(testData[i].operations);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
