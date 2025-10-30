#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minNumberOperations(vector<int>& target) {
        int retVal = 0;

        int targetSize = target.size();
        retVal = target[0];
        for (int i = 1; i < targetSize; ++i) {
            retVal += max(target[i] - target[i - 1], 0);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> target;
    };
    vector<subject> testData{{{1, 1, 2}}, {{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = [1,2,3,2,1]
     *  Output: 3
     *
     *  Input: target = [3,1,1,2]
     *  Output: 4
     *
     *  Input: target = [3,1,5,4,2]
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = [";
        for (long unsigned int j = 0; j < testData[i].target.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].target[j];
        }
        cout << "]\n";

        answer = cSolution.minNumberOperations(testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
