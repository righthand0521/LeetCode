#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string addBinary(string a, string b) {
        string retVal;

        int sum;
        int carry = 0;
        int idxA = a.length() - 1;
        int idxB = b.length() - 1;
        while ((idxA >= 0) && (idxB >= 0)) {
            sum = (a[idxA--] - '0') + (b[idxB--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        while (idxA >= 0) {
            sum = (a[idxA--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        while (idxB >= 0) {
            sum = (b[idxB--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        if (carry == 1) {
            retVal = (char)((carry + '0')) + retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string a;
        string b;
    };
    vector<subject> testData{{"11", "1"}, {"1010", "1011"}, {"0", "0"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: a = "11", b = "1"
     *  Output: "100"
     *
     *  Input: a = "1010", b = "1011"
     *  Output: "10101"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: a = \"" << testData[i].a << "\", b = \"" << testData[i].b << "\"\n";

        answer = cSolution.addBinary(testData[i].a, testData[i].b);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
