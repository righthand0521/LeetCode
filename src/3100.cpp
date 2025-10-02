#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int retVal = numBottles;

        for (int empty = numBottles; empty >= numExchange; numExchange++) {
            retVal++;
            empty -= (numExchange - 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numBottles;
        int numExchange;
    };
    vector<subject> testData{{13, 6}, {10, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numBottles = 13, numExchange = 6
     *  Output: 15
     *
     *  Input: numBottles = 10, numExchange = 3
     *  Output: 13
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numBottles = " << testData[i].numBottles << ", numExchange = " << testData[i].numExchange
             << "\n";

        answer = cSolution.maxBottlesDrunk(testData[i].numBottles, testData[i].numExchange);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
