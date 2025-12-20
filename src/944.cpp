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
        for (int i = 0; i < strSize; ++i) {
            for (int j = 1; j < strsSize; ++j) {
                if (strs[j - 1][i] > strs[j][i]) {
                    ++retVal;
                    break;
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
    vector<subject> testData{{{"cba", "daf", "ghi"}}, {{"a", "b"}}, {{"zyx", "wvu", "tsr"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["cba","daf","ghi"]
     *  Output: 1
     *
     *  Input: strs = ["a","b"]
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
