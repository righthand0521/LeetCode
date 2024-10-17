#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumSwap(int num) {
        int retVal = 0;

        string numStr = to_string(num);
        int numStrSize = numStr.size();
        int maxDigitIndex = -1;
        int swapIdx1 = -1;
        int swapIdx2 = -1;
        for (int i = numStrSize - 1; i >= 0; --i) {
            if ((maxDigitIndex == -1) || (numStr[i] > numStr[maxDigitIndex])) {
                maxDigitIndex = i;
            } else if (numStr[i] < numStr[maxDigitIndex]) {
                swapIdx1 = i;
                swapIdx2 = maxDigitIndex;
            }
        }

        if ((swapIdx1 != -1) && (swapIdx2 != -1)) {
            swap(numStr[swapIdx1], numStr[swapIdx2]);
        }
        retVal = stoi(numStr);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{2736}, {9973}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 2736
     *  Output: 7236
     *
     *  Input: num = 9973
     *  Output: 9973
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.maximumSwap(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
