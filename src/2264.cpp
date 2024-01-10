#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string largestGoodInteger(string num) {
        string retVal = "";

        int numSize = num.size();
        if (numSize < 3) {  // 3 <= num.length <= 1000
            return retVal;
        }

        char goodChar = 0;
        for (int i = 2; i < numSize; ++i) {
            if ((num[i - 2] != num[i - 1]) || (num[i - 1] != num[i])) {
                continue;
            } else if (goodChar >= num[i - 2]) {
                continue;
            }
            goodChar = num[i - 2];
        }
        if (goodChar != 0) {
            retVal = string(3, goodChar);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num;
    };
    vector<subject> testData{{"6777133339"}, {"2300019"}, {"42352338"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = "6777133339"
     *  Output: "777"
     *
     *  Input: num = "2300019"
     *  Output: "000"
     *
     *  Input: num = "42352338"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].num << "\"\n";

        answer = cSolution.largestGoodInteger(testData[i].num);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
