#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int lettersSize = 26;  // s1 and s2 consist of lowercase English letters.

   public:
    bool checkInclusion(string s1, string s2) {
        bool retVal = false;

        int s1Size = s1.size();
        int s2Size = s2.size();
        if (s2Size < s1Size) {
            return retVal;
        }

        vector<int> count1(lettersSize, 0);
        vector<int> count2(lettersSize, 0);

        for (int i = 0; i < s1Size; ++i) {
            ++count1[s1[i] - 'a'];
            ++count2[s2[i] - 'a'];
        }
        if (count1 == count2) {
            retVal = true;
            return retVal;
        }

        for (int i = s1Size; i < s2Size; ++i) {
            ++count2[s2[i] - 'a'];
            --count2[s2[i - s1Size] - 'a'];
            if (count1 == count2) {
                retVal = true;
                return retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s1;
        string s2;
    };
    vector<subject> testData{{"ab", "eidbaooo"}, {"ab", "eidboaoo"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "ab", s2 = "eidbaooo"
     *  Output: true
     *
     *  Input: s1 = "ab", s2 = "eidboaoo"
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << "\", s2 = \"" << testData[i].s2 << "\"\n";

        answer = cSolution.checkInclusion(testData[i].s1, testData[i].s2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
