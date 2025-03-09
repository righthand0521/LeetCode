#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int retVal = 0;

        int colorsSize = colors.size();
        int alternatingElementsCount = 1;
        int lastColor = colors[0];
        for (int i = 1; i < colorsSize + k - 1; i++) {
            int index = i % colorsSize;

            // Check if current color is the same as last color
            if (colors[index] == lastColor) {
                // Pattern breaks, reset sequence length
                alternatingElementsCount = 1;
                lastColor = colors[index];
                continue;
            }

            // Extend alternating sequence
            alternatingElementsCount += 1;

            // If sequence length reaches at least k, count it
            if (alternatingElementsCount >= k) {
                retVal++;
            }

            lastColor = colors[index];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> colors;
        int k;
    };
    vector<subject> testData{{{0, 1, 0, 1, 0}, 3}, {{0, 1, 0, 0, 1, 0, 1}, 6}, {{1, 1, 0, 1}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: colors = [0,1,0,1,0], k = 3
     *  Output: 3
     *
     *  Input: colors = [0,1,0,0,1,0,1], k = 6
     *  Output: 2
     *
     *  Input: colors = [1,1,0,1], k = 4
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: colors = [";
        for (long unsigned int j = 0; j < testData[i].colors.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].colors[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.numberOfAlternatingGroups(testData[i].colors, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
