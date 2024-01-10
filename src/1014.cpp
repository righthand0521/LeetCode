#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int retVal = 0;

        // The score of a pair (i < j) of sightseeing spots is
        // values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
        int maxScore = values[0] + 0;
        int valuesSize = values.size();
        for (int i = 1; i < valuesSize; ++i) {
            retVal = max(retVal, (maxScore + values[i] - i));
            maxScore = max(maxScore, values[i] + i);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> values;
    };
    vector<subject> testData{{{8, 1, 5, 2, 6}}, {{1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: values = [8,1,5,2,6]
     *  Output: 11
     *
     *  Input: values = [1,2]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: values = [";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].values[j];
        }
        cout << "]\n";

        answer = cSolution.maxScoreSightseeingPair(testData[i].values);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
