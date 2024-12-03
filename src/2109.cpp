#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string addSpaces(string s, vector<int>& spaces) {
        string retVal = "";

        int sSize = s.size();
        int spacesSize = spaces.size();

        int sIdx = 0;
        int spacesIdx = 0;
        while (sIdx < sSize) {
            if ((spacesIdx < spacesSize) && (sIdx == spaces[spacesIdx])) {
                retVal += ' ';
                spacesIdx++;
                continue;
            }
            retVal += s[sIdx];
            sIdx++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<int> spaces;
    };
    vector<subject> testData{
        {"LeetcodeHelpsMeLearn", {8, 13, 15}}, {"icodeinpython", {1, 5, 7, 9}}, {"spacing", {0, 1, 2, 3, 4, 5, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
     *  Output: "Leetcode Helps Me Learn"
     *
     *  Input: s = "icodeinpython", spaces = [1,5,7,9]
     *  Output: "i code in py thon"
     *
     *  Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
     *  Output: " s p a c i n g"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", spaces = [";
        for (long unsigned int j = 0; j < testData[i].spaces.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].spaces[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.addSpaces(testData[i].s, testData[i].spaces);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
