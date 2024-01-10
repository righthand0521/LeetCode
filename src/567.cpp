#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MAX_COUNT_SIZE (26)  // s1 and s2 consist of lowercase English letters.
   public:
    bool checkInclusion(string s1, string s2) {
        bool retVal = false;

        int len1 = s1.length();
        int len2 = s2.length();
        if (len2 < len1) {
            return retVal;
        }

        vector<int> count1(MAX_COUNT_SIZE, 0);
        vector<int> count2(MAX_COUNT_SIZE, 0);

        for (int i = 0; i < len1; ++i) {
            ++count1[s1[i] - 'a'];
            ++count2[s2[i] - 'a'];
        }
        if (count1 == count2) {
            retVal = true;
            return retVal;
        }

        for (int i = len1; i < len2; ++i) {
            ++count2[s2[i] - 'a'];
            --count2[s2[i - len1] - 'a'];
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
