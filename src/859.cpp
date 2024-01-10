#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool buddyStrings(string s, string goal) {
        bool retVal = false;

        int sSize = s.size();
        int goalSize = goal.size();
        if (sSize != goalSize) {
            return retVal;
        }

        if (s == goal) {
            // If we have 2 same characters in string 's', we can swap them and still strings will remain equal.
            vector<int> frequency(26, 0);
            for (auto& ch : s) {
                frequency[ch - 'a'] += 1;
                if (frequency[ch - 'a'] == 2) {
                    retVal = true;
                    return retVal;
                }
            }

            // Otherwise, if we swap any two chanacters it will make strings unequal.
            return retVal;
        }

        int firstIndex = -1;
        int secondIndex = -1;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] != goal[i]) {
                if (firstIndex == -1) {
                    firstIndex = i;
                } else if (secondIndex == -1) {
                    secondIndex = i;
                } else {
                    // We have atleast 3 indices with differnet characters,
                    // thus, we can never make strings equal with only one swap.
                    return retVal;
                }
            }
        }

        if (secondIndex == -1) {
            // We can't swap if character at only one index is different.
            return retVal;
        }

        // All characters of both the string are same except two indices.
        retVal = ((s[firstIndex] == goal[secondIndex]) && (s[secondIndex] == goal[firstIndex]));

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string goal;
    };
    vector<subject> testData{{"ab", "ba"},    {"ab", "ab"},       {"aa", "aa"},
                             {"ab", "babbb"}, {"abcaa", "abcbb"}, {"abcd", "abcd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ab", goal = "ba"
     *  Output: true
     *
     *  Input: s = "ab", goal = "ab"
     *  Output: false
     *
     *  Input: s = "aa", goal = "aa"
     *  Output: true
     *
     *  Input: s = "ab", goal = "babbb"
     *  Output: false
     *
     *  Input: s = "abcaa", goal = "abcbb
     *  Output: false
     *
     *  Input: s = "abcd", goal = "abcd"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", goal = \"" << testData[i].goal << "\"\n";

        answer = cSolution.buddyStrings(testData[i].s, testData[i].goal);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
