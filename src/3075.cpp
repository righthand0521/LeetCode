#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        long long retVal = 0;

        sort(happiness.begin(), happiness.end(), greater<int>());
        for (int i = 0; i < k; ++i) {
            int happy = happiness[i] - i;
            if (happy <= 0) {
                break;
            }
            retVal += happy;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> happiness;
        int k;
    };
    vector<subject> testData{{{1, 2, 3}, 2}, {{1, 1, 1, 1}, 2}, {{2, 3, 4, 5}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: happiness = [1,2,3], k = 2
     *  Output: 4
     *
     *  Input: happiness = [1,1,1,1], k = 2
     *  Output: 1
     *
     *  Input: happiness = [2,3,4,5], k = 1
     *  Output: 5
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: happiness = [";
        for (long unsigned int j = 0; j < testData[i].happiness.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].happiness[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumHappinessSum(testData[i].happiness, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
