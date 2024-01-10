#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    // https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    long long putMarbles(vector<int>& weights, int k) {
        long long retVal = 0;

        /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
         *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
         *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
         *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
         *
         *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
         *
         *  1. 對weights進行兩兩求和得到map
         *  2. map中挑k-1個值，並累和得到sum
         *  3. 求出sum的最大值和最小值並做差
         */
        int weightsSize = weights.size();
        vector<long long> map;
        for (int i = 1; i < weightsSize; i++) {
            map.emplace_back(weights[i] + weights[i - 1]);
        }
        sort(map.begin(), map.end());
        int mapSize = map.size();

        long long minimumScores = 0;
        long long maximumScores = 0;
        for (int i = 0; i < k - 1; i++) {
            minimumScores += map[i];
            maximumScores += map[mapSize - 1 - i];
        }
        retVal = maximumScores - minimumScores;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> weights;
        int k;
    };
    vector<subject> testData{{{1, 3, 5, 1}, 2}, {{1, 3}, 2}, {{11}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: weights = [1,3,5,1], k = 2
     *  Output: 4
     *
     *  Input: weights = [1, 3], k = 2
     *  Output: 0
     *
     *  Input: weights = [11], k = 1
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: weights = [";
        for (long unsigned int j = 0; j < testData[i].weights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].weights[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.putMarbles(testData[i].weights, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
