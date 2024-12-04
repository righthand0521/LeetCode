#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canMakeSubsequence(string str1, string str2) {
        bool retVal = false;

        int str1Size = str1.size();
        int str2Size = str2.size();

        int str2Index = 0;
        for (int str1Index = 0; (str1Index < str1Size && str2Index < str2Size); ++str1Index) {
            if (str1[str1Index] == str2[str2Index]) {
                str2Index++;
            } else if (str1[str1Index] + 1 == str2[str2Index]) {
                str2Index++;
            } else if (str1[str1Index] - 25 == str2[str2Index]) {
                str2Index++;
            }
        }

        if (str2Index == str2Size) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string str1;
        string str2;
    };
    vector<subject> testData{{"abc", "ad"}, {"zc", "ad"}, {"ab", "d"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: str1 = "abc", str2 = "ad"
     *  Output: true
     *
     *  Input: str1 = "zc", str2 = "ad"
     *  Output: true
     *
     *  Input: str1 = "ab", str2 = "d"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: str1 = \"" << testData[i].str1 << "\"";
        cout << ", str2 = \"" << testData[i].str2 << "\"\n";

        answer = cSolution.canMakeSubsequence(testData[i].str1, testData[i].str2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
