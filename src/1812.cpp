#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool squareIsWhite(string coordinates) {
        bool retVal = false;

        if (coordinates.length() != 2) {
            return retVal;
        }

        int row = coordinates[0] - 'a';
        int col = coordinates[1] - '0';
        if (((row % 2) == 0) && ((col % 2) == 0)) {
            retVal = true;
        } else if (((row % 2) == 1) && ((col % 2) == 1)) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string coordinates;
    };
    vector<subject> testData{{"a1"}, {"h3"}, {"c7"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: coordinates = "a1"
     *  Output: false
     *
     *  Input: coordinates = "h3"
     *  Output: true
     *
     *  Input: coordinates = "c7"
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: coordinates = \"" << testData[i].coordinates << "\"\n";

        answer = cSolution.squareIsWhite(testData[i].coordinates);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
