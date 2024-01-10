#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestWPI(vector<int>& hours) {
        int retVal = 0;

        int hoursSize = hours.size();

        vector<int> prefixSum(hoursSize + 1, 0);
        stack<int> monotonicStack;
        monotonicStack.push(0);
        for (int i = 1; i <= hoursSize; ++i) {
            prefixSum[i] = prefixSum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (prefixSum[monotonicStack.top()] > prefixSum[i]) {
                monotonicStack.push(i);
            }
        }

        for (int i = hoursSize; i >= 1; --i) {
            while ((monotonicStack.size()) && (prefixSum[monotonicStack.top()] < prefixSum[i])) {
                retVal = max(retVal, i - monotonicStack.top());
                monotonicStack.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> hours;
    };
    vector<subject> testData{
        {{9, 9, 6, 0, 6, 6, 9}}, {{6, 6, 6}}, {{9, 9, 6, 9, 0, 6, 9, 6, 9}}, {{6, 9, 6}}, {{6, 9, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: hours = [9,9,6,0,6,6,9]
     *  Output: 3
     *
     *  Input: hours = [6,6,6]
     *  Output: 0
     *
     *  Input: hours = [9,9,6,9,0,6,9,6,9]
     *  Output: 9
     *
     *  Input: hours = [6,9,6]
     *  Output: 1
     *
     *  Input: hours = [6,9,9]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: hours = [";
        for (long unsigned int j = 0; j < testData[i].hours.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].hours[j];
        }
        cout << "]\n";

        answer = cSolution.longestWPI(testData[i].hours);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
