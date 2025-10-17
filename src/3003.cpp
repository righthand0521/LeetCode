#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxPartitionsAfterOperations(string s, int k) {
        int retVal = 0;

        int sSize = s.length();
        vector<vector<int>> left(sSize, vector<int>(3));
        vector<vector<int>> right(sSize, vector<int>(3));
        int num, mask, count;

        num = 0;
        mask = 0;
        count = 0;
        for (int i = 0; i < sSize - 1; i++) {
            int binary = 1 << (s[i] - 'a');
            if (!(mask & binary)) {
                count++;
                if (count <= k) {
                    mask |= binary;
                } else {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }
            left[i + 1][0] = num;
            left[i + 1][1] = mask;
            left[i + 1][2] = count;
        }

        num = 0;
        mask = 0;
        count = 0;
        for (int i = sSize - 1; i > 0; i--) {
            int binary = 1 << (s[i] - 'a');
            if (!(mask & binary)) {
                count++;
                if (count <= k) {
                    mask |= binary;
                } else {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }
            right[i - 1][0] = num;
            right[i - 1][1] = mask;
            right[i - 1][2] = count;
        }

        int maxLetters = 26;  // s consists only of lowercase English letters.
        for (int i = 0; i < sSize; i++) {
            int seg = left[i][0] + right[i][0] + 2;
            int totMask = left[i][1] | right[i][1];
            int totCount = 0;
            while (totMask) {
                totMask = totMask & (totMask - 1);
                totCount++;
            }
            if ((left[i][2] == k) && (right[i][2] == k) && (totCount < maxLetters)) {
                seg++;
            } else if (min(totCount + 1, maxLetters) <= k) {
                seg--;
            }
            retVal = max(retVal, seg);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"accca", 2}, {"aabaab", 3}, {"xxyz", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "accca", k = 2
     *  Output: 3
     *
     *  Input: s = "aabaab", k = 3
     *  Output: 1
     *
     *  Input: s = "xxyz", k = 1
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.maxPartitionsAfterOperations(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
