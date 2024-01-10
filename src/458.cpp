#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int retVal = 0;

        /* https://leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
         *  pow(base, answer) ≥ buckets
         *  => answer ≥ log(buckets) / log(base)
         *  => answer = ceil(log(buckets) / log(base))
         */
        int base = minutesToTest / minutesToDie + 1;
        retVal = ceil(log10(buckets) / log10(base));

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int buckets;
        int minutesToDie;
        int minutesToTest;
    };
    vector<subject> testData{{4, 15, 15}, {4, 15, 30}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
     *  Output: 2
     *
     *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: buckets = " << testData[i].buckets << ", minutesToDie = " << testData[i].minutesToDie
             << ", minutesToTest = " << testData[i].minutesToTest << "\n";

        answer = cSolution.poorPigs(testData[i].buckets, testData[i].minutesToDie, testData[i].minutesToTest);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
