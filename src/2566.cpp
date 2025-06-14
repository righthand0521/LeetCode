#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMaxDifference(int num) {
        int retVal = 0;

        string numMaxStr = to_string(num);
        size_t idx = numMaxStr.find_first_not_of('9');
        if (idx != string::npos) {
            char a = numMaxStr[idx];
            replace(numMaxStr.begin(), numMaxStr.end(), a, '9');
        }

        string numMinStr = to_string(num);
        char b = numMinStr[0];
        replace(numMinStr.begin(), numMinStr.end(), b, '0');

        retVal = stoi(numMaxStr) - stoi(numMinStr);

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{11891}, {90}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 11891
     *  Output: 99009
     *
     *  Input: num = 90
     *  Output: 99
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.minMaxDifference(testData[i].num);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
