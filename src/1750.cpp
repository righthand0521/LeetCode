#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumLength(string s) {
        int retVal = 0;

        int left = 0;
        int right = s.size() - 1;
        while ((left < right) && (s[left] == s[right])) {
            char equal = s[left];
            while ((left <= right) && (s[left] == equal)) {
                ++left;
            }
            while ((left <= right) && (s[right] == equal)) {
                --right;
            }
        }
        retVal = right - left + 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"ca"}, {"cabaabac"}, {"aabccabba"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ca"
     *  Output: 2
     *
     *  Input: s = "cabaabac"
     *  Output: 0
     *
     *  Input: s = "aabccabba"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minimumLength(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
