#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canConstruct(string s, int k) {
        int retVal = false;

        int sSize = s.size();
        if (sSize < k) {
            return retVal;
        } else if (sSize == k) {
            retVal = true;
            return retVal;
        }

        vector<int> frequency(26, 0);  // s consists of lowercase English letters.
        for (auto& chr : s) {
            frequency[chr - 'a']++;
        }

        int oddCount = 0;
        for (auto count : frequency) {
            if (count % 2 == 1) {
                oddCount++;
            }
        }

        if (oddCount <= k) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"annabelle", 2}, {"leetcode", 3}, {"true", 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "annabelle", k = 2
     *  Output: true
     *
     *  Input: s = "leetcode", k = 3
     *  Output: false
     *
     *  Input: s = "true", k = 4
     *  Output: true
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.canConstruct(testData[i].s, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
