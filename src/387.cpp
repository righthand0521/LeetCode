#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int firstUniqChar(string s) {
        int retVal = -1;

        int sSize = s.size();

        unordered_map<char, int> hashTable;
        for (int i = 0; i < sSize; ++i) {
            hashTable[s[i]] += 1;
        }

        for (int i = 0; i < sSize; ++i) {
            if (hashTable[s[i]] == 1) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"leetcode"}, {"loveleetcode"}, {"aabb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "leetcode"
     *  Output: 0
     *
     *  Input: s = "loveleetcode"
     *  Output: 2
     *
     *  Input: s = "aabb"
     *  Output: -1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.firstUniqChar(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
