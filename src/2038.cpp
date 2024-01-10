#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool winnerOfGame(string colors) {
        bool retVal = false;

        int colorsSize = colors.size();

        int Alice = 0;
        int Bob = 0;
        for (int i = 1; i < colorsSize - 1; ++i) {
            // The number of moves available to Alice is the number of times the substring "AAA" appears.
            // The number of moves available to Bob is the number of times the substring "BBB" appears.
            if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
                if (colors[i] == 'A') {
                    Alice++;
                } else if (colors[i] == 'B') {
                    Bob++;
                }
            }
        }
        if (Alice > Bob) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string colors;
    };
    vector<subject> testData{{"AAABABB"}, {"AA"}, {"ABBBBBBBAAA"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: colors = "AAABABB"
     *  Output: true
     *
     *  Input: colors = "AA"
     *  Output: false
     *
     *  Input: colors = "ABBBBBBBAAA"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: colors = \"" << testData[i].colors << "\"\n";

        answer = cSolution.winnerOfGame(testData[i].colors);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
