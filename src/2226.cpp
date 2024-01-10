#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumCandies(vector<int>& candies, long long k) {
        int retVal = 0;

        int left = 1;
        int right = 1 + (*max_element(candies.begin(), candies.end()));
        while (left < right) {
            int middle = left + (right - left) / 2;

            long long tmpCandies = 0;
            for (auto candy : candies) {
                tmpCandies += (candy / middle);
            }

            if (tmpCandies >= k) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left - 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> candies;
        long long k;
    };
    vector<subject> testData{
        {{5, 8, 6}, 3}, {{2, 5}, 11}, {{1, 2, 3, 4, 10}, 5}, {{4, 7, 5}, 16}, {{5, 6, 4, 10, 10, 1, 1, 2, 2, 2}, 9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: candies = [5,8,6], k = 3
     *  Output: 5
     *
     *  Input: candies = [2,5], k = 11
     *  Output: 0
     *
     *  Input: candies = [1, 2, 3, 4, 10], k = 5
     *  Output: 3
     *
     *  Input: candies = [4, 7, 5], k = 16
     *  Output: 1
     *
     *  Input: candies = [5, 6, 4, 10, 10, 1, 1, 2, 2, 2], k = 9
     *  Output: 3
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: candies = [";
        for (long unsigned int j = 0; j < testData[i].candies.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].candies[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumCandies(testData[i].candies, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
