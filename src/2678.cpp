#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSeniors(vector<string>& details) {
        int retVal = 0;

        for (string detail : details) {
            int age = 10 * (detail[11] - '0') + (detail[12] - '0');
            if (age > 60) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> details;
    };
    vector<subject> testData{{{"7868190130M7522", "5303914400F9211", "9273338290F4010"}},
                             {{"1313579440F2036", "2921522980M5644"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: details = ["7868190130M7522","5303914400F9211","9273338290F4010"]
     *  Output: 2
     *
     *  Input: details = ["1313579440F2036","2921522980M5644"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: details = [";
        for (long unsigned int j = 0; j < testData[i].details.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[\"";
            for (long unsigned int k = 0; k < testData[i].details[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].details[j][k];
            }
            cout << "\"]";
        }
        cout << "]\n";

        answer = cSolution.countSeniors(testData[i].details);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
