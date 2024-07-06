#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int passThePillow(int n, int time) {
        int retVal = 0;

        int direction = time / (n - 1);
        int index = time % (n - 1);
        if (direction % 2 == 0) {
            retVal = index + 1;
        } else if (direction % 2 == 1) {
            retVal = n - index;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int time;
    };
    vector<subject> testData{{4, 5}, {3, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, time = 5
     *  Output: 2
     *
     *  Input: n = 3, time = 2
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", time = " << testData[i].time << "\n";

        answer = cSolution.passThePillow(testData[i].n, testData[i].time);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
