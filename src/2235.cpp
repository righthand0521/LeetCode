#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int sum(int num1, int num2) {
        int retVal = num1 + num2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num1;
        int num2;
    };
    vector<subject> testData{{12, 5}, {-10, 4}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num1 = " << testData[i].num1 << ", num2 = " << testData[i].num2 << "\n";

        answer = cSolution.sum(testData[i].num1, testData[i].num2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
