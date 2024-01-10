#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int getMaximumConsecutive(vector<int>& coins) {
        int retVal = 1;

        sort(coins.begin(), coins.end());
        for (auto iter : coins) {
            // Return the maximum number of consecutive integer values
            // that you can make with your coins starting from and including 0.
            if (iter > retVal) {
                break;
            }
            retVal += iter;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> coins;
    };
    vector<subject> testData{
        {{1, 3}},
        {{1, 1, 1, 4}},
        {{1, 4, 10, 3, 1}},
        {{1, 89, 8, 1, 47, 34, 99, 1, 1, 1, 55, 89, 1, 52, 36, 1, 62, 1, 1, 1, 4, 27, 1, 45, 1, 1, 48, 1, 94, 1, 63}},
        {{2, 3, 4}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: coins = [";
        for (long unsigned int j = 0; j < testData[i].coins.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].coins[j];
        }
        cout << "]\n";

        answer = cSolution.getMaximumConsecutive(testData[i].coins);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
