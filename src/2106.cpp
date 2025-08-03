#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int step(vector<vector<int>>& fruits, int startPos, int left, int right) {
        int retVal = 0;

        if (fruits[right][0] <= startPos) {
            retVal = startPos - fruits[left][0];
        } else if (fruits[left][0] >= startPos) {
            retVal = fruits[right][0] - startPos;
        } else {
            retVal = min(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]));
            retVal += fruits[right][0];
            retVal -= fruits[left][0];
        }

        return retVal;
    }

   public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int retVal = 0;

        int fruitsSize = fruits.size();

        int sum = 0;
        int left = 0;
        int right = 0;
        while (right < fruitsSize) {
            sum += fruits[right][1];

            while ((left <= right) && (step(fruits, startPos, left, right) > k)) {
                sum -= fruits[left][1];
                left++;
            }
            retVal = max(retVal, sum);

            right++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> fruits;
        int startPos;
        int k;
    };
    vector<subject> testData{{{{2, 8}, {6, 3}, {8, 6}}, 5, 4},
                             {{{0, 9}, {4, 1}, {5, 7}, {6, 2}, {7, 4}, {10, 9}}, 5, 4},
                             {{{0, 3}, {6, 4}, {8, 5}}, 3, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
     *  Output: 9
     *
     *  Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
     *  Output: 14
     *
     *  Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
     *  Output: 0
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
        cout << "], startPos = " << testData[i].startPos << ", k = " << testData[i].k << "\n";

        answer = cSolution.maxTotalFruits(testData[i].fruits, testData[i].startPos, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
