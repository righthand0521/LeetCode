#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numWaterBottles(int numBottles, int numExchange) {
        int retVal = 0;

        int consumedBottles = 0;
        while (numBottles >= numExchange) {
            int times = numBottles / numExchange;
            consumedBottles += (numExchange * times);
            numBottles -= (numExchange * times);
            numBottles += times;
        }
        retVal = consumedBottles + numBottles;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numBottles;
        int numExchange;
    };
    vector<subject> testData{{9, 3}, {15, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numBottles = 9, numExchange = 3
     *  Output: 13
     *
     *  Input: numBottles = 15, numExchange = 4
     *  Output: 19
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numBottles = " << testData[i].numBottles << ", numExchange = " << testData[i].numExchange
             << "\n";

        answer = cSolution.numWaterBottles(testData[i].numBottles, testData[i].numExchange);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
