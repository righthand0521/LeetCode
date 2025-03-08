#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumRecolors(string blocks, int k) {
        int retVal = k;

        int blocksSize = blocks.size();
        int left = 0;
        int numWhites = 0;
        for (int right = 0; right < blocksSize; right++) {
            if (blocks[right] == 'W') {
                numWhites++;
            }

            if (right - left + 1 == k) {
                retVal = min(retVal, numWhites);

                if (blocks[left] == 'W') {
                    numWhites--;
                }

                left++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string blocks;
        int k;
    };
    vector<subject> testData{{"WBBWWBBWBW", 7}, {"WBWBBBW", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: blocks = "WBBWWBBWBW", k = 7
     *  Output: 3
     *
     *  Input: blocks = "WBWBBBW", k = 2
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: blocks = \"" << testData[i].blocks << "\", k = " << testData[i].k << "\n";

        answer = cSolution.minimumRecolors(testData[i].blocks, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
