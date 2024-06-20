#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
    bool canPlaceBalls(int x, vector<int>& position, int m) {
        bool retVal = false;

        int positionSize = position.size();

        // Place the first ball at the first position.
        int prevBallPos = position[0];
        int ballsPlaced = 1;

        // Iterate on each 'position' and place a ball there if we can place it.
        for (int i = 1; i < positionSize && ballsPlaced < m; ++i) {
            int currPos = position[i];

            // Check if we can place the ball at the current position.
            if (currPos - prevBallPos >= x) {
                ballsPlaced += 1;
                prevBallPos = currPos;
            }
        }
        // If all 'm' balls are placed, return 'true'.
        if (ballsPlaced == m) {
            retVal = true;
        }

        return retVal;
    }
    int maxDistance(vector<int>& position, int m) {
        int retVal = 0;

        int positionSize = position.size();

        sort(position.begin(), position.end());

        // Initial search space.
        int low = 1;
        int high = ceil(position[positionSize - 1] / (m - 1.0));
        while (low <= high) {
            int middle = low + (high - low) / 2;

            // If we can place all balls having a gap at least 'mid',
            if (canPlaceBalls(middle, position, m)) {
                retVal = middle;   // then 'mid' can be our answer,
                low = middle + 1;  // and discard the left half search space.
            } else {
                high = middle - 1;  // Discard the right half search space.
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> position;
        int m;
    };
    vector<subject> testData{{{1, 2, 3, 4, 7}, 3}, {{5, 4, 3, 2, 1, 1000000000}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: position = [1,2,3,4,7], m = 3
     *  Output: 3
     *
     *  Input: position = [5,4,3,2,1,1000000000], m = 2
     *  Output: 999999999
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: position = [";
        for (long unsigned int j = 0; j < testData[i].position.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].position[j];
        }
        cout << "], m = " << testData[i].m << "\n";

        answer = cSolution.maxDistance(testData[i].position, testData[i].m);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
