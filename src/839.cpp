#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int find(vector<int>& f, int x) {
        int retVal = x;

        if (f[x] == x) {
            return retVal;
        }
        f[x] = find(f, f[x]);
        retVal = f[x];

        return retVal;
    }
    bool check(const string& a, const string& b, int len) {
        bool retVal = false;

        int num = 0;
        for (int i = 0; i < len; ++i) {
            if (a[i] == b[i]) {
                continue;
            }
            num++;
            if (num > 2) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
    int numSimilarGroups(vector<string>& strs) {
        int retVal = 0;

        int strsSize = strs.size();
        vector<int> f(strsSize);
        for (int i = 0; i < strsSize; ++i) {
            f[i] = i;
        }

        for (int i = 0; i < strsSize; ++i) {
            for (int j = i + 1; j < strsSize; ++j) {
                int fi = find(f, i);
                int fj = find(f, j);
                if (fi == fj) {
                    continue;
                }

                int len = strs[i].length();
                if (check(strs[i], strs[j], len)) {
                    f[fi] = fj;
                }
            }
        }

        for (int i = 0; i < strsSize; ++i) {
            if (f[i] == i) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
    };
    vector<subject> testData{{{"tars", "rats", "arts", "star"}}, {{"omv", "ovm"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["tars","rats","arts","star"]
     *  Output: 2
     *
     *  Input: strs = ["omv","ovm"]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.numSimilarGroups(testData[i].strs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
