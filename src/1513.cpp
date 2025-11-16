#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int numSub(string s) {
        int retVal = 0;

        long long total = 0;
        long long consecutiveOneCount = 0;
        for (char c : s) {
            if (c == '1') {
                ++consecutiveOneCount;
            } else {
                total += (consecutiveOneCount * (consecutiveOneCount + 1) / 2);
                total %= MODULO;
                consecutiveOneCount = 0;
            }
        }
        total += (consecutiveOneCount * (consecutiveOneCount + 1) / 2);
        total %= MODULO;

        retVal = static_cast<int>(total);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"0110111"}, {"101"}, {"111111"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "0110111"
     *  Output: 9
     *
     *  Input: s = "101"
     *  Output: 2
     *
     *  Input: s = "111111"
     *  Output: 21
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numSub(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
