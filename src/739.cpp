#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> retVal;

        int temperaturesSize = temperatures.size();
        retVal.resize(temperaturesSize, 0);

        stack<int> monotonicStack;
        for (int i = 0; i < temperaturesSize; ++i) {
            while ((monotonicStack.empty() == false) && (temperatures[i] > temperatures[monotonicStack.top()])) {
                int previousIdx = monotonicStack.top();
                retVal[previousIdx] = i - previousIdx;
                monotonicStack.pop();
            }
            monotonicStack.push(i);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> temperatures;
    };
    vector<subject> testData{{{73, 74, 75, 71, 69, 72, 76, 73}}, {{30, 40, 50, 60}}, {{30, 60, 90}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: temperatures = [73,74,75,71,69,72,76,73]
     *  Output: [1,1,4,2,1,1,0,0]
     *
     *  Input: temperatures = [30,40,50,60]
     *  Output: [1,1,1,0]
     *
     *  Input: temperatures = [30,60,90]
     *  Output: [1,1,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: temperatures = [";
        for (long unsigned int j = 0; j < testData[i].temperatures.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].temperatures[j];
        }
        cout << "]\n";

        answer = cSolution.dailyTemperatures(testData[i].temperatures);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
