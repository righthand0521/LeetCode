#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    char kthCharacter(int k) {
        char retVal;

        int ans = 0;
        while (k != 1) {
            int shift = __lg(k);
            if ((1 << shift) == k) {
                shift--;
            }
            k = k - (1 << shift);
            ans++;
        }
        retVal = 'a' + ans;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
    };
    vector<subject> testData{{5}, {10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 5
     *  Output: "b"
     *
     *  Input: k = 10
     *  Output: "c"
     */

    Solution cSolution;
    char answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << "\n";

        answer = cSolution.kthCharacter(testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
