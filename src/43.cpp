#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string multiply(string num1, string num2) {
        string retVal = "";

        if ((num1 == "0") || (num2 == "0")) {
            retVal = "0";
            return retVal;
        }

        int num1Size = num1.size();
        int num2Size = num2.size();
        int returnSize = num1Size + num2Size;
        vector<int> returnBuf(returnSize, 0);
        for (int i = num1Size - 1; i >= 0; --i) {
            int multiplicand = num1[i] - '0';
            for (int j = num2Size - 1; j >= 0; --j) {
                int multiplier = num2[j] - '0';
                int product = multiplicand * multiplier;
                returnBuf[i + j + 1] = returnBuf[i + j + 1] + product;
                int carry = (returnBuf[i + j + 1]) / 10;
                returnBuf[i + j + 1] = (returnBuf[i + j + 1] % 10);
                returnBuf[i + j] = returnBuf[i + j] + carry;
            }
        }

        if (returnBuf[0] != 0) {
            retVal += to_string(returnBuf[0]);
        }
        for (int i = 1; i < returnSize; ++i) {
            retVal += to_string(returnBuf[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string num1;
        string num2;
    };
    vector<subject> testData{{"2", "3"}, {"123", "456"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num1 = "2", num2 = "3"
     *  Output: "6"
     *
     *  Input: num1 = "123", num2 = "456"
     *  Output: "56088"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num1 = \"" << testData[i].num1 << "\", num2 = \"" << testData[i].num2 << "\"\n";

        answer = cSolution.multiply(testData[i].num1, testData[i].num2);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
