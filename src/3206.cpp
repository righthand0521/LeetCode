#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int retVal = 0;

        int colorsSize = colors.size();
        for (int i = 0; i < colorsSize; ++i) {
            if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
                continue;
            } else if (colors[i] == colors[(i + 1) % colorsSize]) {
                continue;
            }
            retVal++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> colors;
    };
    vector<subject> testData{{{1, 1, 1}}, {{0, 1, 0, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: colors = [1,1,1]
     *  Output: 0
     *
     *  Input: colors = [0,1,0,0,1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: colors = [";
        for (long unsigned int j = 0; j < testData[i].colors.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].colors[j];
        }
        cout << "]\n";

        answer = cSolution.numberOfAlternatingGroups(testData[i].colors);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
