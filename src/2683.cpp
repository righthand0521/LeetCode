#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool doesValidArrayExist(vector<int>& derived) {
        bool retVal = false;

        int XOR = 0;
        for (auto element : derived) {
            XOR = XOR ^ element;
        }
        if (XOR == 0) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> derived;
    };
    vector<subject> testData{{{1, 1, 0}}, {{1, 1}}, {{1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: derived = [1,1,0]
     *  Output: true
     *
     *  Input: derived = [1,1]
     *  Output: true
     *
     *  Input: derived = [1,0]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: derived = [";
        for (long unsigned int j = 0; j < testData[i].derived.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].derived[j];
        }
        cout << "]\n";

        answer = cSolution.doesValidArrayExist(testData[i].derived);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
