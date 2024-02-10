#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSubstrings(string s) {
        int retVal = 0;

        int sSize = s.size();

        for (int i = 0; i < (2 * sSize - 1); ++i) {
            int left = i / 2;
            int right = i / 2 + i % 2;
            while ((left >= 0) && (right < sSize) && (s[left] == s[right])) {
                --left;
                ++right;
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
    vector<subject> testData{{"abc"}, {"aaa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abc"
     *  Output: 3
     *
     *  Input: s = "aaa"
     *  Output: 6
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.countSubstrings(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
