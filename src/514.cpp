#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    // Find the minimum steps between two indexes of ring
    int countSteps(int curr, int next, int ringLength) {
        int retVal = 0;

        int stepsBetween = abs(curr - next);
        int stepsAround = ringLength - stepsBetween;
        retVal = min(stepsBetween, stepsAround);

        return retVal;
    }

   public:
    int findRotateSteps(string ring, string key) {
        int retVal = 0;

        int ringSize = ring.size();
        int keySize = key.size();

        vector<int> curr(ringSize, 0);
        vector<int> prev(ringSize, 0);
        fill(prev.begin(), prev.end(), 0);
        // For each occurrence of the character at key_index of key in ring
        // Stores minimum steps to the character from ringIndex of ring
        for (int keyIndex = keySize - 1; keyIndex >= 0; keyIndex--) {
            fill(curr.begin(), curr.end(), numeric_limits<int>::max());
            for (int ringIndex = 0; ringIndex < ringSize; ringIndex++) {
                for (int charIndex = 0; charIndex < ringSize; charIndex++) {
                    if (ring[charIndex] == key[keyIndex]) {
                        curr[ringIndex] =
                            min(curr[ringIndex], 1 + countSteps(ringIndex, charIndex, ringSize) + prev[charIndex]);
                    }
                }
            }
            prev = curr;
        }
        retVal = prev[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string ring;
        string key;
    };
    vector<subject> testData{{"godding", "gd"}, {"godding", "godding"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: ring = "godding", key = "gd"
     *  Output: 4
     *
     *  Input: ring = "godding", key = "godding"
     *  Output: 13
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: ring = \"" << testData[i].ring << "\", key = \"" << testData[i].key << "\"\n";

        answer = cSolution.findRotateSteps(testData[i].ring, testData[i].key);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
