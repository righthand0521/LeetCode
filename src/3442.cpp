#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDifference(string s) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }

        int maxOdd = 0;
        int minEven = s.size();
        for (const auto& [key, value] : frequency) {
            if (value % 2 == 1) {
                maxOdd = max(maxOdd, value);
            } else {
                minEven = min(minEven, value);
            }
        }
        retVal = maxOdd - minEven;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aaaaabbc"}, {"abcabcab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaaaabbc"
     *  Output: 3
     *
     *  Input: s = "abcabcab"
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxDifference(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
