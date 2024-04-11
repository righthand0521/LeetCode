#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string removeKdigits(string num, int k) {
        string retVal = "";

        vector<char> numStack;
        for (auto c : num) {
            while ((k > 0) && (numStack.empty() == false) && (numStack.back() > c)) {
                numStack.pop_back();
                k--;
            }
            numStack.emplace_back(c);
        }

        while (k > 0) {
            numStack.pop_back();
            k--;
        }

        bool leadingZeros = true;
        for (auto c : numStack) {
            if ((leadingZeros == true) && (c == '0')) {
                continue;
            }
            leadingZeros = false;
            retVal += c;
        }
        if (retVal == "") {
            retVal = "0";
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num;
        int k;
    };
    vector<subject> testData{{"1432219", 3}, {"10200", 1}, {"10", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = "1432219", k = 3
     *  Output: "1219"
     *
     *  Input: num = "10200", k = 1
     *  Output: "200"
     *
     *  Input: num = "10", k = 2
     *  Output: "0"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = \"" << testData[i].num << "\", k = " << testData[i].k << "\n";

        answer = cSolution.removeKdigits(testData[i].num, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
