#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.

   public:
    int lengthAfterTransformations(string s, int t) {
        int retVal = 0;

        vector<int> hashTable(letterSize, 0);
        for (char ch : s) {
            ++hashTable[ch - 'a'];
        }

        for (int round = 0; round < t; ++round) {
            vector<int> next(letterSize, 0);
            next[0] = hashTable[letterSize - 1];
            next[1] = (hashTable[letterSize - 1] + hashTable[0]) % MODULO;
            for (int i = 2; i < letterSize; ++i) {
                next[i] = hashTable[i - 1];
            }
            hashTable = move(next);
        }

        for (int i = 0; i < letterSize; ++i) {
            retVal = (retVal + hashTable[i]) % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int t;
    };
    vector<subject> testData{{"abcyy", 2}, {"azbk", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcyy", t = 2
     *  Output: 7
     *
     *  Input: s = "azbk", t = 1
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = " << testData[i].t << "\n";

        answer = cSolution.lengthAfterTransformations(testData[i].s, testData[i].t);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
