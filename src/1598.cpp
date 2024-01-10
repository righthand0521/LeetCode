#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<string>& logs) {
        int retVal = 0;

        int logsSize = logs.size();
        for (int i = 0; i < logsSize; ++i) {
            if (logs[i] == "../") {
                if (retVal > 0) {
                    retVal--;
                }
            } else if (logs[i] == "./") {
                continue;
            } else {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> logs;
    };
    vector<subject> testData{{{"d1/", "d2/", "../", "d21/", "./"}},
                             {{"d1/", "d2/", "./", "d3/", "../", "d31/"}},
                             {{"d1/", "../", "../", "../"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: logs = ["d1/","d2/","../","d21/","./"]
     *  Output: 2
     *
     *  Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
     *  Output: 3
     *
     *  Input: logs = ["d1/","../","../","../"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: logs = [";
        for (long unsigned int j = 0; j < testData[i].logs.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].logs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.minOperations(testData[i].logs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
