#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool areAlmostEqual(string s1, string s2) {
        bool retVal = false;

        int s1Size = s1.size();
        int count = 0;
        int record[2] = {0};
        for (int i = 0; i < s1Size; ++i) {
            if (s1[i] == s2[i]) {
                continue;
            }
            record[0] |= (1 << (s1[i] - 'a'));
            record[1] |= (1 << (s2[i] - 'a'));
            ++count;
        }

        if (count == 0) {
            retVal = true;
        } else if ((count == 2) && (record[0] == record[1])) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s1;
        string s2;
    };
    vector<subject> testData{{{"bank"}, {"kanb"}}, {{"attack"}, {"defend"}}, {{"kelb"}, {"kelb"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "bank", s2 = "kanb"
     *  Output: true
     *
     *  Input: s1 = "attack", s2 = "defend"
     *  Output: false
     *
     *  Input: s1 = "kelb", s2 = "kelb"
     *  Output: true
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << "\", s2 = \"" << testData[i].s2 << "\"\n";

        answer = cSolution.areAlmostEqual(testData[i].s1, testData[i].s2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
