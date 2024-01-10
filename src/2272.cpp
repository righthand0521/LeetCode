#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestVariance(string s) {
        int retVal = 0;

        int sSize = s.size();
        unordered_map<char, vector<int>> pos;
        for (int i = 0; i < sSize; ++i) {
            pos[s[i]].push_back(i);
        }

        for (auto&& [c0, pos0] : pos) {
            for (auto&& [c1, pos1] : pos) {
                if (c0 == c1) {
                    continue;
                }

                int i = 0;
                int j = 0;
                int f = 0;
                int g = numeric_limits<int>::min();
                int pos0Size = pos0.size();
                int pos1Size = pos1.size();
                while (i < pos0Size || j < pos1Size) {
                    if (j == pos1Size || (i < pos0Size && pos0[i] < pos1[j])) {
                        tie(f, g) = tuple{max(f, 0) + 1, g + 1};
                        ++i;
                    } else {
                        tie(f, g) = tuple{max(f, 0) - 1, max({f, g, 0}) - 1};
                        ++j;
                    }

                    retVal = max(retVal, g);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aababbb"}, {"abcde"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aababbb"
     *  Output: 3
     *
     *  Input: s = "abcde"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.largestVariance(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
