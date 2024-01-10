#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int mySqrt(int x) {
        int retVal = 0;

        // Integer square root: Newton's method to find a solution for the equation x^2 - n = 0
        long long root = x;
        while (root * root > x) {
            root = (root + x / root) / 2;
        }
        retVal = (int)root;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int x;
    };
    vector<subject> testData{{4}, {8}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: x = 4
     *  Output: 2
     *
     *  Input: x = 8
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].x << "\n";

        answer = cSolution.mySqrt(testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
