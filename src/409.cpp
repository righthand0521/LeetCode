#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestPalindrome(string s) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (char c : s) {
            ++frequency[c];
        }

        for (auto p : frequency) {
            int value = p.second;
            retVal += (value / 2 * 2);
            if ((value % 2 == 1) && (retVal % 2 == 0)) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abccccdd"}, {"a"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abccccdd"
     *  Output: 7
     *
     *  Input: s = "a"
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.longestPalindrome(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
