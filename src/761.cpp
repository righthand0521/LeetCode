#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string makeLargestSpecial(string s) {
        string retVal = "";

        int sSize = s.size();
        if (sSize <= 2) {
            retVal = s;
            return retVal;
        }

        int cnt = 0;
        int left = 0;
        vector<string> subs;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '1') {
                cnt++;
                continue;
            }
            cnt--;
            if (cnt == 0) {
                subs.push_back("1" + makeLargestSpecial(s.substr(left + 1, i - left - 1)) + "0");
                left = i + 1;
            }
        }
        sort(subs.begin(), subs.end(), greater<string>());
        for (const auto& sub : subs) {
            retVal += sub;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"11011000"}, {"10"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "11011000"
     *  Output: "11100100"
     *
     *  Input: s = "10"
     *  Output: "10"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.makeLargestSpecial(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
