#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Flatten the grid into numsArray
        vector<int> numsArray;
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridColSize; col++) {
                numsArray.push_back(grid[row][col]);
            }
        }
        int numsArraySize = numsArray.size();

        // Partially sorts the array so that the median element is placed at the middle index
        nth_element(numsArray.begin(), numsArray.begin() + numsArraySize / 2, numsArray.end());

        // Store the median element as the final common value to make all elements equal to
        int finalCommonNumber = numsArray[numsArraySize / 2];

        for (int number : numsArray) {
            // If the remainder when divided by x is different for any number, return -1
            if (number % x != finalCommonNumber % x) {
                retVal = -1;
                break;
            }
            // Add the number of operations required to make the current number equal to finalCommonNumber
            retVal += abs(finalCommonNumber - number) / x;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
        int x;
    };
    vector<subject> testData{{{{2, 4}, {6, 8}}, 2}, {{{1, 5}, {2, 3}}, 1}, {{{1, 2}, {3, 4}}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[2,4],[6,8]], x = 2
     *  Output: 4
     *
     *  Input: grid = [[1,5],[2,3]], x = 1
     *  Output: 5
     *
     *  Input: grid = [[1,2],[3,4]], x = 2
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "], x = " << testData[i].x << "\n";

        answer = cSolution.minOperations(testData[i].grid, testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
