#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDeletions(string s) {
        int retVal = 0;

        map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }

        set<int> hashSet;
        for (auto [key, value] : frequency) {
            for (int i = value; i > 0; --i) {
                if (hashSet.count(i) == 0) {
                    hashSet.insert(i);
                    break;
                }
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aab"}, {"aaabbbcc"}, {"ceabaacb"}, {"abc"}, {"aaab"}, {"abcabc"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aab"
     *  Output: 0
     *
     *  Input: s = "aaabbbcc"
     *  Output: 2
     *
     *  Input: s = "ceabaacb"
     *  Output: 2
     *
     *  Input: s = "abc"
     *  Output: 2
     *
     *  Input: s = "aaab"
     *  Output: 0
     *
     *  Input: s = "abcabc"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minDeletions(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
