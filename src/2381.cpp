#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        string retVal = s;

        int sSize = s.size();

        vector<int> diffArray(sSize, 0);
        for (auto shift : shifts) {
            if (shift[2] == 1) {
                diffArray[shift[0]]++;
                if (shift[1] + 1 < sSize) {
                    diffArray[shift[1] + 1]--;
                }
            } else {
                diffArray[shift[0]]--;
                if (shift[1] + 1 < sSize) {
                    diffArray[shift[1] + 1]++;
                }
            }
        }

        int numberOfShifts = 0;
        for (int i = 0; i < sSize; i++) {
            numberOfShifts = (numberOfShifts + diffArray[i]) % 26;
            if (numberOfShifts < 0) {
                numberOfShifts += 26;
            }
            retVal[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<vector<int>> shifts;
    };
    vector<subject> testData{{"abc", {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}}}, {"dztz", {{0, 0, 0}, {1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
     *  Output: "ace"
     *
     *  Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
     *  Output: "catz"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", shifts = [";
        for (long unsigned int j = 0; j < testData[i].shifts.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].shifts[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].shifts[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.shiftingLetters(testData[i].s, testData[i].shifts);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
