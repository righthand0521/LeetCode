#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDeletionSize(vector<string>& strs) {
        int retVal = 0;

        int strsSize = strs.size();
        int strSize = strs[0].size();

        // # cuts[i] is True : we don't need to check col[i] <= col[i+1]
        vector<bool> cuts(strsSize - 1, false);

        for (int j = 0; j < strSize; ++j) {
            bool needDelete = false;

            // Evaluate whether we can keep this column
            for (int i = 0; i < strsSize - 1; ++i) {
                if ((cuts[i] == false) && (strs[i][j] > strs[i + 1][j])) {
                    // Can't keep the column - delete and continue
                    retVal += 1;
                    needDelete = true;
                    break;
                }
            }
            if (needDelete == true) {
                continue;
            }

            // Update 'cuts' information
            for (int i = 0; i < strsSize - 1; ++i) {
                if (strs[i][j] < strs[i + 1][j]) {
                    cuts[i] = true;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
    };
    vector<subject> testData{{{"ca", "bb", "ac"}}, {{"xc", "yb", "za"}}, {{"zyx", "wvu", "tsr"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["ca","bb","ac"]
     *  Output: 1
     *
     *  Input: strs = ["xc","yb","za"]
     *  Output: 0
     *
     *  Input: strs = ["zyx","wvu","tsr"]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.minDeletionSize(testData[i].strs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
