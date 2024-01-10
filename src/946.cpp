#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        bool retVal = false;

        int poppedSize = popped.size();
        int poppedIdx = 0;

        stack<int> stackRecord;
        for (auto value : pushed) {
            stackRecord.push(value);
            int i;
            for (i = poppedIdx; i < poppedSize; ++i) {
                if ((stackRecord.empty() == false) && (stackRecord.top() == popped[i])) {
                    stackRecord.pop();
                } else {
                    poppedIdx = i;
                    break;
                }
            }
        }

        if (stackRecord.empty() == true) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> pushed;
        vector<int> popped;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, {4, 5, 3, 2, 1}}, {{1, 2, 3, 4, 5}, {4, 3, 5, 1, 2}}, {{1, 0}, {1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
     *  Output: true
     *
     *  Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
     *  Output: false
     *
     *  Input: pushed = [1, 0], popped = [1, 0]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pushed = [";
        for (long unsigned int j = 0; j < testData[i].pushed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].pushed[j];
        }
        cout << "], popped = [";
        for (long unsigned int j = 0; j < testData[i].popped.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].popped[j];
        }
        cout << "]\n";

        answer = cSolution.validateStackSequences(testData[i].pushed, testData[i].popped);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
