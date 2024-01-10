#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        bool retVal = false;

        int diffX = abs(fx - sx);
        int diffY = abs(fy - sy);

        if ((diffX == 0) && (diffY == 0)) {
            if (t != 1) {
                retVal = true;
            }
        } else {
            if ((t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY))) {
                retVal = true;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int sx;
        int sy;
        int fx;
        int fy;
        int t;
    };
    vector<subject> testData{{2, 4, 7, 7, 6}, {3, 1, 7, 3, 3}, {1, 2, 1, 2, 1}, {1, 1, 1, 1, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
     *  Output: true
     *
     *  Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
     *  Output: false
     *
     *  Input: sx = 1, sy = 2, fx = 1, fy = 2, t = 1
     *  Output: false
     *
     *  Input: sx = 1, sy = 1, fx = 1, fy = 1, t = 3
     *  Output: true
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: sx = " << testData[i].sx << ", sy = " << testData[i].sy << ", fx = " << testData[i].fx
             << ", fy = " << testData[i].fy << ", t = " << testData[i].t << "\n";

        answer =
            cSolution.isReachableAtTime(testData[i].sx, testData[i].sy, testData[i].fx, testData[i].fy, testData[i].t);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
