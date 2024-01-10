#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    int lettersSize = 26;  // s consists of only lowercase English letters.

   public:
    int countPalindromicSubsequence(string s) {
        int retVal = 0;

        int sSize = s.size();

        vector<int> left(lettersSize, -1);
        vector<int> right(lettersSize, -1);
        for (int i = 0; i < sSize; ++i) {
            int idx = s[i] - 'a';
            if (left[idx] == -1) {
                left[idx] = i;
            }
            right[idx] = i;
        }

        for (int i = 0; i < lettersSize; ++i) {
            if (left[i] == -1) {
                continue;
            }

            unordered_set<char> between;
            for (int j = left[i] + 1; j < right[i]; ++j) {
                between.insert(s[j]);
            }
            retVal += between.size();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aabca"}, {"adc"}, {"bbcbaba"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aabca"
     *  Output: 3
     *
     *  Input: s = "adc"
     *  Output: 0
     *
     *  Input: s = "bbcbaba"
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.countPalindromicSubsequence(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
