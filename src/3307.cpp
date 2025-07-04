#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    char kthCharacter(long long k, vector<int>& operations) {
        char retVal;

        int ans = 0;
        k--;
        for (int i = __lg(k); i >= 0; i--) {
            if (k >> i & 1) {
                ans += operations[i];
            }
        }
        retVal = 'a' + (ans % 26);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        long long k;
        vector<int> operations;
    };
    vector<subject> testData{{5, {0, 0, 0}}, {10, {0, 1, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 5, operations = [0,0,0]
     *  Output: "a"
     *
     *  Input: k = 10, operations = [0,1,0,1]
     *  Output: "b"
     */

    Solution cSolution;
    char answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << ", operations = [";
        for (long unsigned int j = 0; j < testData[i].operations.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].operations[j];
        }
        cout << "]\n";

        answer = cSolution.kthCharacter(testData[i].k, testData[i].operations);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
