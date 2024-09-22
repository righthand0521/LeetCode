#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        int retVal = 0;

        int heightsSize = heights.size();

        vector<int> left(heightsSize, 0);
        vector<int> right(heightsSize, heightsSize);
        stack<int> monotonicStack;
        for (int i = 0; i < heightsSize; ++i) {
            while ((monotonicStack.empty() == false) && (heights[monotonicStack.top()] >= heights[i])) {
                right[monotonicStack.top()] = i;
                monotonicStack.pop();
            }

            left[i] = -1;
            if (monotonicStack.empty() == false) {
                left[i] = monotonicStack.top();
            }

            monotonicStack.push(i);
        }

        for (int i = 0; i < heightsSize; ++i) {
            retVal = max(retVal, (right[i] - left[i] - 1) * heights[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> heights;
    };
    vector<subject> testData{{{2, 1, 5, 6, 2, 3}}, {{2, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [2,1,5,6,2,3]
     *  Output: 10
     *
     *  Input: heights = [2,4]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].heights[j];
        }
        cout << "]\n";

        answer = cSolution.largestRectangleArea(testData[i].heights);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
