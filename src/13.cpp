#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int romanToInt(string s) {
        int retVal = 0;

        unordered_map<char, int> romanMapping = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000},
        };

        // III = I + I + I = 1 + 1 + 1 = 3
        // LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
        // MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
        int currentValue, nextValue;
        int sSize = s.size();
        for (int i = 0; i < sSize - 1; ++i) {
            currentValue = romanMapping[s[i]];
            nextValue = romanMapping[s[i + 1]];
            if (currentValue < nextValue) {
                retVal -= currentValue;
            } else {
                retVal += currentValue;
            }
        }
        currentValue = romanMapping[s[sSize - 1]];
        retVal += currentValue;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"III"}, {"LVIII"}, {"MCMXCIV"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "III"
     *  Output: 3
     *
     *  Input: s = "LVIII"
     *  Output: 58
     *
     *  Input: s = "MCMXCIV"
     *  Output: 1994
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.romanToInt(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
