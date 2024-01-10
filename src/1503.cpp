#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int retVal = 0;

        /* Brainteaser
         *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
         *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
         *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
         *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
         *  假設一隻螞蟻在位置 p。
         *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
         *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
         */
        for (int p : left) {
            retVal = max(retVal, p);
        }
        for (int p : right) {
            retVal = max(retVal, n - p);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> left;
        vector<int> right;
    };
    vector<subject> testData{{4, {4, 3}, {0, 1}}, {7, {}, {0, 1, 2, 3, 4, 5, 6, 7}}, {7, {0, 1, 2, 3, 4, 5, 6, 7}, {}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, left = [4,3], right = [0,1]
     *  Output: 4
     *
     *  Input: n = 7, left = [], right = [0,1,2,3,4,5,6,7]
     *  Output: 7
     *
     *  Input: n = 7, left = [0,1,2,3,4,5,6,7], right = []
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", left = [";
        for (long unsigned int j = 0; j < testData[i].left.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].left[j];
        }
        cout << "], right = [";
        for (long unsigned int j = 0; j < testData[i].right.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].right[j];
        }
        cout << "]\n";

        answer = cSolution.getLastMoment(testData[i].n, testData[i].left, testData[i].right);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
