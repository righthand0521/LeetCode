#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findClosest(int x, int y, int z) {
        int retVal = 0;

        int diffX = abs(z - x);
        int diffY = abs(z - y);
        if (diffX < diffY) {
            retVal = 1;
        } else if (diffX > diffY) {
            retVal = 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int x;
        int y;
        int z;
    };
    vector<subject> testData{{2, 7, 4}, {2, 5, 6}, {1, 5, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: x = 2, y = 7, z = 4
     *  Output: 1
     *
     *  Input: x = 2, y = 5, z = 6
     *  Output: 2
     *
     *  Input: x = 1, y = 5, z = 3
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].x << ", y = " << testData[i].y << ", z = " << testData[i].z << "\n";

        answer = cSolution.findClosest(testData[i].x, testData[i].y, testData[i].z);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
