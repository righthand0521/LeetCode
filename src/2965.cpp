#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        vector<int> retVal(2, 0);

        // Store frequency of each number in the grid
        unordered_map<int, int> freq;
        for (auto& row : grid) {
            for (int num : row) {
                freq[num]++;
            }
        }

        // Check numbers from 1 to n^2 to find missing and repeated values
        int missing = -1;
        int repeat = -1;
        int gridSize = grid.size();
        for (int num = 1; num <= gridSize * gridSize; num++) {
            if (freq.count(num) == 0) {
                missing = num;
            } else if (freq[num] == 2) {
                repeat = num;
            }
        }
        retVal = {repeat, missing};

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 3}, {2, 2}}}, {{{9, 1, 7}, {8, 9, 2}, {3, 4, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,3],[2,2]]
     *  Output: [2,4]
     *
     *  Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
     *  Output: [9,5]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findMissingAndRepeatedValues(testData[i].grid);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
