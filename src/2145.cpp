#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        int retVal = 0;

        int minValue = 0;
        int maxValue = 0;
        int currentSum = 0;
        for (int difference : differences) {
            currentSum += difference;
            minValue = min(minValue, currentSum);
            maxValue = max(maxValue, currentSum);
            if ((maxValue - minValue) > (upper - lower)) {
                return retVal;
            }
        }
        retVal = (upper - lower) - (maxValue - minValue) + 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> differences;
        int lower;
        int upper;
    };
    vector<subject> testData{{{1, -3, 4}, 1, 6}, {{3, -4, 5, 1, -2}, -4, 5}, {{4, -7, 2}, 3, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: differences = [1,-3,4], lower = 1, upper = 6
     *  Output: 2
     *
     *  Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
     *  Output: 4
     *
     *  Input: differences = [4,-7,2], lower = 3, upper = 6
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: differences = [";
        for (long unsigned int j = 0; j < testData[i].differences.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].differences[j];
        }
        cout << "], lower = " << testData[i].lower << ", upper = " << testData[i].upper << "\n";

        answer = cSolution.numberOfArrays(testData[i].differences, testData[i].lower, testData[i].upper);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
