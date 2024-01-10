#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int characterReplacement(string s, int k) {
        int retVal = 0;

        // s consists of only uppercase English letters.
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int sSize = s.length();
        int left = 0;
        int right = 0;
        while (right < sSize) {
            Record[s[right] - 'A']++;

            maxRecord = max(maxRecord, Record[s[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[s[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"ABAB", 2}, {"AABABBA", 1}, {"ABAA", 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ABAB", k = 2
     *  Output: 4
     *
     *  Input: s = "AABABBA", k = 1
     *  Output: 4
     *
     *  Input: s = "ABAA", k = 0
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.characterReplacement(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
