#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int subtractProductAndSum(int n) {
        int retVal;

        int mod;
        int product = 1;
        int sum = 0;
        while (n > 0) {
            mod = n % 10;
            product *= mod;
            sum += mod;
            n /= 10;
        }
        retVal = product - sum;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{234}, {4421}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.subtractProductAndSum(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
