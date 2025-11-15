#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfSubstrings(string s) {
        int retVal = 0;

        int sSize = s.size();

        vector<int> pre(sSize + 1);
        pre[0] = -1;
        for (int i = 0; i < sSize; i++) {
            if ((i == 0) || ((i > 0) && (s[i - 1] == '0'))) {
                pre[i + 1] = i;
            } else {
                pre[i + 1] = pre[i];
            }
        }

        for (int i = 1; i <= sSize; i++) {
            int cnt0 = s[i - 1] == '0';
            int j = i;
            while ((j > 0) && (cnt0 * cnt0 <= sSize)) {
                int cnt1 = (i - pre[j]) - cnt0;
                if (cnt0 * cnt0 <= cnt1) {
                    retVal += min(j - pre[j], cnt1 - cnt0 * cnt0 + 1);
                }
                j = pre[j];
                cnt0++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"00011"}, {"101101"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "00011"
     *  Output: 5
     *
     *  Input: s = "101101"
     *  Output: 16
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numberOfSubstrings(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
