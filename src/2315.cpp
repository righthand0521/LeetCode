#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countAsterisks(string s) {
        int retVal = 0;

        int verticalBars = 0;
        for (auto c : s) {
            if (c == '|') {
                ++verticalBars;
                continue;
            }

            if (verticalBars % 2 == 1) {
                continue;
            }

            if (c == '*') {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"l|*e*et|c**o|*de|"}, {"iamprogrammer"}, {"yo|uar|e**|b|e***au|tifu|l"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.countAsterisks(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
