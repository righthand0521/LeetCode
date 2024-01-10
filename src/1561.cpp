#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxCoins(vector<int>& piles) {
        int retVal = 0;

        int pilesSize = piles.size();
        sort(piles.begin(), piles.end());

        int left = 0;
        int right = pilesSize - 1;
        while (left < right) {
            --right;
            retVal += piles[right];
            --right;
            ++left;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> piles;
    };
    vector<subject> testData{{{2, 4, 1, 2, 7, 8}}, {{2, 4, 5}}, {{9, 8, 7, 6, 5, 1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: piles = [2,4,1,2,7,8]
     *  Output: 9
     *
     *  Input: piles = [2,4,5]
     *  Output: 4
     *
     *  Input: piles = [9,8,7,6,5,1,2,3,4]
     *  Output: 18
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: piles = [";
        for (long unsigned int j = 0; j < testData[i].piles.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].piles[j];
        }
        cout << "]\n";

        answer = cSolution.maxCoins(testData[i].piles);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
