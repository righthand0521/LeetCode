#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfBeams(vector<string>& bank) {
        int retVal = 0;

        int previous = 0;
        for (string row : bank) {
            int count = 0;
            for (char c : row) {
                if (c == '1') {
                    count++;
                }
            }

            if (count != 0) {
                retVal += (previous * count);
                previous = count;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> bank;
    };
    vector<subject> testData{{{"011001", "000000", "010100", "001000"}}, {{"000", "111", "000"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: bank = ["011001","000000","010100","001000"]
     *  Output: 8
     *
     *  Input: bank = ["000","111","000"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bank = [";
        for (long unsigned int j = 0; j < testData[i].bank.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].bank[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.numberOfBeams(testData[i].bank);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
