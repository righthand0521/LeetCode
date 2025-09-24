#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string fractionToDecimal(int numerator, int denominator) {
        string retVal;

        long numeratorLong = numerator;
        long denominatorLong = denominator;
        if (numeratorLong % denominatorLong == 0) {
            retVal = to_string(numeratorLong / denominatorLong);
            return retVal;
        }

        //
        if ((numeratorLong < 0) ^ (denominatorLong < 0)) {
            retVal.push_back('-');
        }
        //
        numeratorLong = abs(numeratorLong);
        denominatorLong = abs(denominatorLong);
        long integerPart = numeratorLong / denominatorLong;
        retVal += to_string(integerPart);
        retVal.push_back('.');
        //
        string fractionPart;
        unordered_map<long, int> remainderIndexMap;
        long remainder = numeratorLong % denominatorLong;
        int index = 0;
        while (remainder != 0 && !remainderIndexMap.count(remainder)) {
            remainderIndexMap[remainder] = index;
            remainder *= 10;
            fractionPart += to_string(remainder / denominatorLong);
            remainder %= denominatorLong;
            index++;
        }
        //
        if (remainder != 0) {
            int insertIndex = remainderIndexMap[remainder];
            fractionPart = fractionPart.substr(0, insertIndex) + '(' + fractionPart.substr(insertIndex);
            fractionPart.push_back(')');
        }
        //
        retVal += fractionPart;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numerator;
        int denominator;
    };
    vector<subject> testData{{1, 2}, {2, 1}, {4, 333}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numerator = 1, denominator = 2
     *  Output: "0.5"
     *
     *  Input: numerator = 2, denominator = 1
     *  Output: "2"
     *
     *  Input: numerator = 4, denominator = 333
     *  Output: "0.(012)"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numerator = " << testData[i].numerator << ", denominator = " << testData[i].denominator << "\n";

        answer = cSolution.fractionToDecimal(testData[i].numerator, testData[i].denominator);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
