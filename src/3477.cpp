#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int retVal = 0;

        int basketsSize = baskets.size();
        for (auto fruit : fruits) {
            int unset = 1;
            for (int i = 0; i < basketsSize; i++) {
                if (fruit <= baskets[i]) {
                    baskets[i] = 0;
                    unset = 0;
                    break;
                }
            }
            retVal += unset;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> fruits;
        vector<int> baskets;
    };
    vector<subject> testData{{{4, 2, 5}, {3, 5, 4}}, {{3, 6, 1}, {6, 4, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: fruits = [4,2,5], baskets = [3,5,4]
     *  Output: 1
     *
     *  Input: fruits = [3,6,1], baskets = [6,4,7]
     *  Output: 0
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: fruits = [";
        for (long unsigned int j = 0; j < testData[i].fruits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].fruits[j];
        }
        cout << "], baskets = [";
        for (long unsigned int j = 0; j < testData[i].baskets.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].baskets[j];
        }
        cout << "]\n";

        answer = cSolution.numOfUnplacedFruits(testData[i].fruits, testData[i].baskets);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
