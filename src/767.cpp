#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string reorganizeString(string s) {
        string retVal;

        int maxCount = -1;
        unordered_map<char, int> count;
        for (auto c : s) {
            ++count[c];
            maxCount = max(maxCount, count[c]);
        }

        int sSize = s.size();
        if (maxCount > ((sSize + 1) / 2)) {
            return retVal;
        }

        string sortS = s;
        sort(sortS.begin(), sortS.end(),
             [&count](char a, char b) { return count[a] > count[b] || (count[a] == count[b] && a > b); });
        retVal = s;
        int idx = 0;
        for (auto c : sortS) {
            retVal[idx] = c;
            idx += 2;
            if (idx >= sSize) {
                idx = 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aab"}, {"aaab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aab"
     *  Output: "aba"
     *
     *  Input: s = "aaab"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.reorganizeString(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
