#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isOneBitCharacter(vector<int>& bits) {
        bool retVal = false;

        int i = bits.size() - 2;
        while ((i >= 0) && (bits[i] > 0)) {
            i--;
        }
        retVal = ((bits.size() - i) % 2 == 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> bits;
    };
    vector<subject> testData{{{1, 0, 0}}, {{1, 1, 1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input: bits = [1,0,0]
     *  Output: true
     *
     *  Input: bits = [1,1,1,0]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bits = [";
        for (long unsigned int j = 0; j < testData[i].bits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].bits[j];
        }
        cout << "]\n";

        answer = cSolution.isOneBitCharacter(testData[i].bits);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
