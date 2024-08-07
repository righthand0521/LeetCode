#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string numberToWords(int num) {
        string retVal;

        if (num == 0) {
            retVal = "Zero";
            return retVal;
        }

        vector<string> ones{"",         "One",     "Two",     "Three",     "Four",     "Five",    "Six",
                            "Seven",    "Eight",   "Nine",    "Ten",       "Eleven",   "Twelve",  "Thirteen",
                            "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        vector<string> tens{"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands{"", "Thousand", "Million", "Billion"};

        int groupIndex = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                string groupResult = "";
                int part = num % 1000;

                if (part >= 100) {
                    groupResult += ones[part / 100] + " Hundred ";
                    part %= 100;
                }

                if (part >= 20) {
                    groupResult += tens[part / 10] + " ";
                    part %= 10;
                }

                if (part > 0) {
                    groupResult += ones[part] + " ";
                }

                groupResult += thousands[groupIndex] + " ";
                retVal = groupResult + retVal;
            }

            num /= 1000;
            groupIndex += 1;
        }

        retVal = retVal.substr(0, retVal.find_last_not_of(" ") + 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{123}, {12345}, {1234567}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 123
     *  Output: "One Hundred Twenty Three"
     *
     *  Input: num = 12345
     *  Output: "Twelve Thousand Three Hundred Forty Five"
     *
     *  Input: num = 1234567
     *  Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.numberToWords(testData[i].num);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
