#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfMatches(int n) {
        int retVal = 0;

        while (n > 1) {
            int next = n >> 1;
            n -= next;
            retVal += next;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{7}, {14}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 7
     *  Output: 6
     *
     *  Input: n = 14
     *  Output: 13
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.numberOfMatches(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
