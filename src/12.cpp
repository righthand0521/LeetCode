#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    string intToRoman(int num) {
        string retVal;

        map<int, string> romanMapping = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
                                         {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
                                         {5, "V"},    {4, "IV"},   {1, "I"}};
        for (auto iterate = romanMapping.rbegin(); iterate != romanMapping.rend(); ++iterate) {
            int key = iterate->first;
            string value = iterate->second;

            while ((num > 0) && ((num - key) >= 0)) {
                num -= key;
                retVal += value;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int num;
    };
    vector<subject> testData{{3}, {58}, {1994}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = 3
     *  Output: "III"
     *
     *  Input: num = 58
     *  Output: "LVIII"
     *
     *  Input: num = 1994
     *  Output: "MCMXCIV"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].num << "\n";

        answer = cSolution.intToRoman(testData[i].num);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
