#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int appendCharacters(string s, string t) {
        int retVal = 0;

        int sSize = s.size();
        int tSize = t.size();

        int idxS = 0;
        int idxT = 0;
        while ((idxS < sSize) && (idxT < tSize)) {
            if (s[idxS] == t[idxT]) {
                idxT += 1;
            }
            idxS += 1;
        }
        retVal = tSize - idxT;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"coaching", "coding"}, {"abcde", "a"}, {"z", "abcde"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "coaching", t = "coding"
     *  Output: 4
     *
     *  Input: s = "abcde", t = "a"
     *  Output: 0
     *
     *  Input: s = "z", t = "abcde"
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.appendCharacters(testData[i].s, testData[i].t);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
