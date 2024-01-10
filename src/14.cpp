#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string longestCommonPrefix(vector<string>& strs) {
        string retVal;

        retVal = strs[0];  // 1 <= strs.length <= 200
        int retValLength = retVal.size();
        int strsSize = strs.size();
        for (int i = 1; i < strsSize; ++i) {
            for (int j = 0; j < retValLength; ++j) {
                if ((j == (int)strs[i].size()) || (retVal[j] != strs[i][j])) {
                    retValLength = j;
                    break;
                }
            }
        }
        retVal = retVal.substr(0, retValLength);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
    };
    vector<subject> testData{{{"flower", "flow", "flight"}}, {{"dog", "racecar", "car"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["flower","flow","flight"]
     *  Output: "fl"
     *
     *  Input: strs = ["dog","racecar","car"]
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.longestCommonPrefix(testData[i].strs);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
