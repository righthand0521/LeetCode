#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxLengthBetweenEqualCharacters(string s) {
        int retVal = -1;

        int sSize = s.size();

#define MAX_LETTERS (26)  // s contains only lowercase English letters.
        vector<int> hashTable(MAX_LETTERS, -1);
        for (int i = 0; i < sSize; ++i) {
            int idx = s[i] - 'a';
            if (hashTable[idx] != -1) {
                retVal = max(retVal, i - hashTable[idx] - 1);
            } else {
                hashTable[idx] = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aa"}, {"abca"}, {"cbzxy"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aa"
     *  Output: 0
     *
     *  Input: s = "abca"
     *  Output: 2
     *
     *  Input: s = "cbzxy"
     *  Output: -1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maxLengthBetweenEqualCharacters(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
