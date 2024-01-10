#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string largestOddNumber(string num) {
        string retVal = "";

        int numSize = num.size();
        for (int i = numSize - 1; i >= 0; --i) {
            if ((num[i] - '0') % 2 == 0) {
                continue;
            }
            retVal = num.substr(0, i + 1);
            break;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num;
    };
    vector<subject> testData{{"52"}, {"4206"}, {"35427"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = "52"
     *  Output: "5"
     *
     *  Input: num = "4206"
     *  Output: ""
     *
     *  Input: num = "35427"
     *  Output: "35427"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].num << "\"\n";

        answer = cSolution.largestOddNumber(testData[i].num);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
