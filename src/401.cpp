#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> retVal;

        for (int hours = 0; hours < 12; ++hours) {         // represent the hours (0-11)
            for (int minute = 0; minute < 60; ++minute) {  // represent the minutes (0-59)
                if (__builtin_popcount(hours) + __builtin_popcount(minute) == turnedOn) {
                    retVal.push_back(to_string(hours) + ":" + ((minute < 10) ? ("0") : ("")) + to_string(minute));
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: turnedOn = 1
     *  Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
     *
     *  Input: turnedOn = 9
     *  Output: []
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.readBinaryWatch(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
