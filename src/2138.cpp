#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> retVal;

        int sSize = s.size();
        int numberOfSubstrings = (sSize + k - 1) / k;
        for (int i = 0; i < numberOfSubstrings; ++i) {
            string part = s.substr(i * k, k);
            int partSize = part.size();
            if (partSize < k) {
                part += string(k - partSize, fill);
            }
            retVal.emplace_back(part);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
        char fill;
    };
    vector<subject> testData{{"abcdefghi", 3, 'x'}, {"abcdefghij", 3, 'x'}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcdefghi", k = 3, fill = "x"
     *  Output: ["abc","def","ghi"]
     *
     *  Input: s = "abcdefghij", k = 3, fill = "x"
     *  Output: ["abc","def","ghi","jxx"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << ", fill = \"" << testData[i].fill
             << "\"\n";

        answer = cSolution.divideString(testData[i].s, testData[i].k, testData[i].fill);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
