#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> retVal;

        sort(potions.begin(), potions.end());
        for (auto spell : spells) {
            long divisor = (success + spell - 1) / spell;
            auto iterator = lower_bound(potions.begin(), potions.end(), divisor);
            retVal.emplace_back(potions.end() - iterator);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> spells;
        vector<int> potions;
        long long success;
    };
    vector<subject> testData{{{5, 1, 3}, {1, 2, 3, 4, 5}, 7}, {{3, 1, 2}, {8, 5, 8}, 16}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
     *  Output: [4,0,3]
     *
     *  Input: spells = [3,1,2], potions = [8,5,8], success = 16
     *  Output: [2,0,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: spells = [";
        for (long unsigned int j = 0; j < testData[i].spells.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].spells[j];
        }
        cout << "], potions = [";
        for (long unsigned int j = 0; j < testData[i].potions.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].potions[j];
        }
        cout << "], success = " << testData[i].success << "\n";

        answer = cSolution.successfulPairs(testData[i].spells, testData[i].potions, testData[i].success);
        cout << "Output = [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
