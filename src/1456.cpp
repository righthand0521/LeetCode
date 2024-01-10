#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxVowels(string s, int k) {
        int retVal = 0;

        vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        int count = 0;
        for (int i = 0; i < k; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                    break;
                }
            }
        }
        retVal = count;

        int sSize = s.size();
        for (int i = k; i < sSize; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                }

                if (s[i - k] == c) {
                    --count;
                }
            }
            retVal = max(retVal, count);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"abciiidef", 3}, {"aeiou", 2}, {"leetcode", 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abciiidef", k = 3
     *  Output: 3
     *
     *  Input: s = "aeiou", k = 2
     *  Output: 2
     *
     *  Input: s = "leetcode", k = 3
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.maxVowels(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
