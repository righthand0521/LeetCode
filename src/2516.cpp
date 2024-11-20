#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int lettersSize = 3;  // s consists of only the letters 'a', 'b', and 'c'.

   public:
    int takeCharacters(string s, int k) {
        int retVal = -1;

        int sSize = s.length();

        // Count total occurrences
        vector<int> count(lettersSize, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Check if we have enough characters
        for (int i = 0; i < lettersSize; i++) {
            if (count[i] < k) {
                return retVal;
            }
        }

        // Find the longest window that leaves k of each character outside
        vector<int> window(lettersSize, 0);
        int maxWindow = 0;
        int left = 0;
        for (int right = 0; right < sSize; right++) {
            window[s[right] - 'a']++;

            // Shrink window if we take too many characters
            while ((left <= right) &&
                   ((count[0] - window[0] < k) || (count[1] - window[1] < k) || (count[2] - window[2] < k))) {
                window[s[left] - 'a']--;
                left++;
            }

            maxWindow = max(maxWindow, right - left + 1);
        }

        retVal = sSize - maxWindow;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"aabaaaacaabc", 2}, {"a", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aabaaaacaabc", k = 2
     *  Output: 8
     *
     *  Input: s = "a", k = 1
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.takeCharacters(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
