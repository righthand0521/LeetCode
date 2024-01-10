#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MAX_COUNT_SIZE (26)  // s and p consist of lowercase English letters.
   public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> retVal;

        int lenS = s.length();
        int lenP = p.length();
        if (lenS < lenP) {
            return retVal;
        }

        vector<int> countS(MAX_COUNT_SIZE, 0);
        vector<int> countP(MAX_COUNT_SIZE, 0);
        for (int i = 0; i < lenP; ++i) {
            ++countS[s[i] - 'a'];
            ++countP[p[i] - 'a'];
        }
        if (countS == countP) {
            retVal.push_back(0);
        }

        for (int i = lenP; i < lenS; ++i) {
            ++countS[s[i] - 'a'];
            --countS[s[i - lenP] - 'a'];
            if (countS == countP) {
                retVal.push_back(i - lenP + 1);
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
