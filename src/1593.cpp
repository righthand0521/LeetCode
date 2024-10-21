#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    int backtrack(const string& s, int start, unordered_set<string>& seen) {
        int retVal = 0;

        int sSize = s.size();

        // Base case: If we reach the end of the string, return 0 (no more substrings to add)
        if (start == sSize) {
            return retVal;
        }

        // Try every possible substring starting from 'start'
        for (int end = start + 1; end <= sSize; ++end) {
            string substring = s.substr(start, end - start);
            if (seen.find(substring) == seen.end()) {  // If the substring is unique
                // Add the substring to the seen set
                seen.insert(substring);
                // Recursively count unique substrings from the next position
                retVal = max(retVal, 1 + backtrack(s, end, seen));
                // Backtrack: remove the substring from the seen set
                seen.erase(substring);
            }
        }

        return retVal;
    }

   public:
    int maxUniqueSplit(string s) {
        int retVal = 0;

        unordered_set<string> seen;
        retVal = backtrack(s, 0, seen);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"ababccc"}, {"aba"}, {"aa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "ababccc"
     *  Output: 5
     *
     *  Input: s = "aba"
     *  Output: 2
     *
     *  Input: s = "aa"
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxUniqueSplit(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
