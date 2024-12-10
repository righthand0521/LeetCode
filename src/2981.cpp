#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumLength(string s) {
        int retVal = 0;

        map<pair<char, int>, int> hashTable;
        char character;
        int substringLength;
        int count;

        int sSize = s.size();
        substringLength = 0;
        for (int start = 0; start < sSize; start++) {
            character = s[start];
            substringLength = 0;
            for (int end = start; end < sSize; end++) {
                // If the string is empty, or the current character is equal to the previously added character,
                // then add it to the map. Otherwise, break the iteration.
                if (character != s[end]) {
                    break;
                }
                substringLength++;
                hashTable[{character, substringLength}]++;
            }
        }

        for (auto iterator : hashTable) {
            character = iterator.first.first;
            substringLength = iterator.first.second;
            count = iterator.second;
            if ((count >= 3) && (substringLength > retVal)) {
                retVal = substringLength;
            }
        }
        if (retVal == 0) {
            retVal = -1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aaaa"}, {"abcdef"}, {"abcaba"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaaa"
     *  Output: 2
     *
     *  Input: s = "abcdef"
     *  Output: -1
     *
     *  Input: s = "abcaba"
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.maximumLength(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
