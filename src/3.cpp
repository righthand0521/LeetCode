#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = s.length();
        int head = 0;
        int tail = 0;
        while ((head < len) && (tail < len)) {
            if ((hashTable[s[head]] != 0) && (hashTable[s[tail]] != 0)) {
                hashTable[s[head]] = 0;
                ++head;
            } else {
                ++hashTable[s[tail]];
                ++tail;
            }
            retVal = max(retVal, (tail - head));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abcabcbb"}, {"bbbbb"}, {"pwwkew"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcabcbb"
     *  Output: 3
     *
     *  Input: s = "bbbbb"
     *  Output: 1
     *
     *  Input: s = "pwwkew"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.lengthOfLongestSubstring(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
