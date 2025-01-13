#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumLength(string s) {
        int retVal = 0;

        vector<int> charFrequency(26, 0);  // s consists only of lowercase English letters.
        for (char currentChar : s) {
            charFrequency[currentChar - 'a']++;
        }

        for (int frequency : charFrequency) {
            if (frequency == 0) {
                continue;
            }

            if (frequency % 2 == 0) {
                retVal += 2;
            } else {
                retVal += 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abaacbcbb"}, {"aa"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abaacbcbb"
     *  Output: 5
     *
     *  Input: s = "aa"
     *  Output: 2
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
