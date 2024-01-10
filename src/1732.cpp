#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestAltitude(vector<int>& gain) {
        int retVal = 0;

        int prefixSum = retVal;
        for (auto iterator : gain) {
            prefixSum += iterator;
            retVal = max(retVal, prefixSum);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> gain;
    };
    vector<subject> testData{{{-5, 1, 5, 0, -7}}, {{-4, -3, -2, -1, 4, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: gain = [-5,1,5,0,-7]
     *  Output: 1
     *
     *  Input: gain = [-4,-3,-2,-1,4,3,2]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: gain = [";
        for (long unsigned int j = 0; j < testData[i].gain.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].gain[j];
        }
        cout << "]\n";

        answer = cSolution.largestAltitude(testData[i].gain);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
