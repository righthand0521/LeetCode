#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestBalanced(string s) {
        int retVal = 0;

        int sSize = s.size();
        
        vector<int> hashTable(26);  // s consists of lowercase English letters.
        for (int i = 0; i < sSize; i++) {
            fill(hashTable.begin(), hashTable.end(), 0);
            for (int j = i; j < sSize; j++) {
                bool flag = true;
                int c = s[j] - 'a';
                hashTable[c]++;
                for (auto x : hashTable) {
                    if ((x > 0) && (x != hashTable[c])) {
                        flag = false;
                        break;
                    }
                }

                if (flag == true) {
                    retVal = max(retVal, j - i + 1);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abbac"}, {"zzabccy"}, {"aba"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abbac"
     *  Output: 4
     *
     *  Input: s = "zzabccy"
     *  Output: 4
     *
     *  Input: s = "aba"
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.longestBalanced(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
