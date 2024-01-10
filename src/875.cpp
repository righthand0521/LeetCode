#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int retVal;

        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            int useHour = 0;
            for (auto pile : piles) {
                // ceiling of an integer division
                useHour += ((pile + middle - 1) / middle);
            }
            if (useHour > h) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> piles;
        int h;
    };
    vector<subject> testData{{{3, 6, 7, 11}, 8}, {{30, 11, 23, 4, 20}, 5}, {{30, 11, 23, 4, 20}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: piles = [3,6,7,11], h = 8
     *  Output: 4
     *
     *  Input: piles = [30,11,23,4,20], h = 5
     *  Output: 30
     *
     *  Input: piles = [30,11,23,4,20], h = 6
     *  Output: 23
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: piles = [";
        for (long unsigned int j = 0; j < testData[i].piles.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].piles[j];
        }
        cout << "], h = " << testData[i].h << "\n";

        answer = cSolution.minEatingSpeed(testData[i].piles, testData[i].h);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
