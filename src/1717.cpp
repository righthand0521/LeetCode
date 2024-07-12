#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumGain(string s, int x, int y) {
        int retVal = 0;

        // Ensure "ab" always has more points than "ba"
        if (x < y) {
            int temp = x;
            x = y;
            y = temp;
            reverse(s.begin(), s.end());
        }

        int aCount = 0;
        int bCount = 0;
        for (auto c : s) {
            if (c == 'a') {
                ++aCount;
            } else if (c == 'b') {
                if (aCount > 0) {
                    --aCount;
                    retVal += x;
                } else {
                    ++bCount;
                }
            } else {
                retVal += min(bCount, aCount) * y;
                aCount = 0;
                bCount = 0;
            }
        }
        retVal += min(bCount, aCount) * y;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int x;
        int y;
    };
    vector<subject> testData{{"cdbcbbaaabab", 4, 5}, {"aabbaaxybbaabb", 5, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "cdbcbbaaabab", x = 4, y = 5
     *  Output: 19
     *
     *  Input: s = "aabbaaxybbaabb", x = 5, y = 4
     *  Output: 20
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", x = " << testData[i].x << ", y = " << testData[i].y << "\n";

        answer = cSolution.maximumGain(testData[i].s, testData[i].x, testData[i].y);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
