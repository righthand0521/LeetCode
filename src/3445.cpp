#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    const int minValue = numeric_limits<int>::min();
    const int maxValue = numeric_limits<int>::max();
    int getStatus(int aCurrent, int bCurrent) {
        int retVal = ((aCurrent & 1) << 1) | (bCurrent & 1);

        return retVal;
    }

   public:
    int maxDifference(string s, int k) {
        int retVal = minValue;

        int sSize = s.size();
        for (char a = '0'; a <= '4'; ++a) {      // s consists only of digits '0' to '4'.
            for (char b = '0'; b <= '4'; ++b) {  // s consists only of digits '0' to '4'.
                if (a == b) {
                    continue;
                }

                int best[4] = {maxValue, maxValue, maxValue, maxValue};
                int aCurrent = 0;
                int bCurrent = 0;
                int aPrevious = 0;
                int bPrevious = 0;
                int left = -1;
                for (int right = 0; right < sSize; ++right) {
                    aCurrent += (s[right] == a);
                    bCurrent += (s[right] == b);
                    while ((right - left >= k) && (bCurrent - bPrevious >= 2)) {
                        int leftStatus = getStatus(aPrevious, bPrevious);
                        best[leftStatus] = min(best[leftStatus], aPrevious - bPrevious);
                        ++left;
                        aPrevious += (s[left] == a);
                        bPrevious += (s[left] == b);
                    }

                    int rightStatus = getStatus(aCurrent, bCurrent);
                    if (best[rightStatus ^ 0b10] != maxValue) {
                        retVal = max(retVal, aCurrent - bCurrent - best[rightStatus ^ 0b10]);
                    }
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"12233", 4}, {"1122211", 3}, {"110", 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "12233", k = 4
     *  Output: -1
     *
     *  Input: s = "1122211", k = 3
     *  Output: 1
     *
     *  Input: s = "110", k = 3
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.maxDifference(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
