#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumEnergy(vector<int>& energy, int k) {
        int retVal = numeric_limits<int>::min();

        int energySize = energy.size();
        for (int i = energySize - k; i < energySize; i++) {
            int sum = 0;
            for (int j = i; j >= 0; j -= k) {
                sum += energy[j];
                retVal = max(retVal, sum);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> energy;
        int k;
    };
    vector<subject> testData{{{5, 2, -10, -5, 1}, 3}, {{-2, -3, -1}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: energy = [5,2,-10,-5,1], k = 3
     *  Output: 3
     *
     *  Input: energy = [-2,-3,-1], k = 2
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: energy = [";
        for (long unsigned int j = 0; j < testData[i].energy.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].energy[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumEnergy(testData[i].energy, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
