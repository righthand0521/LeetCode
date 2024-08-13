#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int letters = 26;  // s and p consist of lowercase English letters.

   public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> retVal;

        int sSize = s.size();
        int pSize = p.size();
        if (sSize < pSize) {
            return retVal;
        }

        vector<int> sCount(letters, 0);
        vector<int> pCount(letters, 0);
        for (int i = 0; i < pSize; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }
        if (sCount == pCount) {
            retVal.emplace_back(0);
        }

        for (int i = pSize; i < sSize; ++i) {
            ++sCount[s[i] - 'a'];
            --sCount[s[i - pSize] - 'a'];
            if (sCount == pCount) {
                retVal.emplace_back(i - pSize + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string p;
    };
    vector<subject> testData{{"cbaebabacd", "abc"}, {"abab", "ab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "cbaebabacd", p = "abc"
     *  Output: [0,6]
     *
     *  Input: s = "abab", p = "ab"
     *  Output: [0,1,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", p = \"" << testData[i].p << "\"\n";

        answer = cSolution.findAnagrams(testData[i].s, testData[i].p);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
