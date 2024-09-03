#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int getLucky(string s, int k) {
        int retVal = 0;

        int sum = 0;
        for (char c : s) {
            int translateToInteger = c - 'a' + 1;
            sum += (translateToInteger % 10);
            sum += (translateToInteger / 10);
        }

        retVal = sum;
        for (int i = 1; i < k; ++i) {
            retVal = 0;
            while (sum > 0) {
                retVal += (sum % 10);
                sum /= 10;
            }
            sum = retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"iiii", 1}, {"leetcode", 2}, {"zbax", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "iiii", k = 1
     *  Output: 36
     *
     *  Input: s = "leetcode", k = 2
     *  Output: 6
     *
     *  Input: s = "zbax", k = 2
     *  Output: 8
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << ", k = " << testData[i].k << "\"\n";

        answer = cSolution.getLucky(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
