#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    int dp(vector<vector<int>>& fruits) {  //    auto dp = [&]() -> int {
        int retVal = 0;

        int fruitsSize = fruits.size();

        vector<int> prev(fruitsSize, numeric_limits<int>::min());
        vector<int> curr(fruitsSize, numeric_limits<int>::min());

        prev[fruitsSize - 1] = fruits[0][fruitsSize - 1];
        for (int i = 1; i < fruitsSize - 1; ++i) {
            for (int j = max(fruitsSize - 1 - i, i + 1); j < fruitsSize; ++j) {
                int best = prev[j];
                if (j - 1 >= 0) {
                    best = max(best, prev[j - 1]);
                }
                if (j + 1 < fruitsSize) {
                    best = max(best, prev[j + 1]);
                }
                curr[j] = best + fruits[i][j];
            }
            swap(prev, curr);
        }
        retVal = prev[fruitsSize - 1];

        return retVal;
    }

   public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int retVal = 0;

        int fruitsSize = fruits.size();

        for (int i = 0; i < fruitsSize; ++i) {
            retVal += fruits[i][i];
        }
        retVal += dp(fruits);

        for (int i = 0; i < fruitsSize; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(fruits[j][i], fruits[i][j]);
            }
        }
        retVal += dp(fruits);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> fruits;
    };
    vector<subject> testData{{{{1, 2, 3, 4}, {5, 6, 8, 7}, {9, 10, 11, 12}, {13, 14, 15, 16}}}, {{{1, 1}, {1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
     *  Output: 100
     *
     *  Input: fruits = [[1,1],[1,1]]
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: fruits = [";
        for (long unsigned int j = 0; j < testData[i].fruits.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].fruits[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].fruits[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxCollectedFruits(testData[i].fruits);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
