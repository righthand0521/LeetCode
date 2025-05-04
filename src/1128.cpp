#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int retVal = 0;

        vector<int> hashTable(100, 0);  // dominoes[i].length == 2, 1 <= dominoes[i][j] <= 9
        for (auto& domino : dominoes) {
            int x = domino[0];
            int y = domino[1];
            int index = (x > y) ? (x * 10 + y) : (y * 10 + x);
            retVal += hashTable[index];
            hashTable[index] += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> dominoes;
    };
    vector<subject> testData{{{{1, 2}, {2, 1}, {3, 4}, {5, 6}}}, {{{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
     *  Output: 1
     *
     *  Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dominoes = [";
        for (long unsigned int j = 0; j < testData[i].dominoes.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].dominoes[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].dominoes[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.numEquivDominoPairs(testData[i].dominoes);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
