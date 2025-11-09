#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countOperations(int num1, int num2) {
        int retVal = 0;

        while ((num1 != 0) && (num2 != 0)) {
            retVal += (num1 / num2);
            num1 %= num2;
            swap(num1, num2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num1;
        int num2;
    };
    vector<subject> testData{{2, 3}, {10, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num1 = 2, num2 = 3
     *  Output: 3
     *
     *  Input: num1 = 10, num2 = 10
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num1 = " << testData[i].num1 << ", num2 = " << testData[i].num2 << "\n";

        answer = cSolution.countOperations(testData[i].num1, testData[i].num2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
