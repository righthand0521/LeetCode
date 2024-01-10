#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> cellsInRange(string s) {
        vector<string> retVal;

        // s.length == 5
        // 'A' <= s[0] <= s[3] <= 'Z'
        // '1' <= s[1] <= s[4] <= '9'
        for (char row = s[0]; row <= s[3]; ++row) {
            for (char col = s[1]; col <= s[4]; ++col) {
                string cell;
                cell.push_back(row);
                cell.push_back(col);
                retVal.emplace_back(cell);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"K1:L2"}, {"A1:F1"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "K1:L2"
     *  Output: ["K1","K2","L1","L2"]
     *
     *  Input: s = "A1:F1"
     *  Output: ["A1","B1","C1","D1","E1","F1"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.cellsInRange(testData[i].s);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
