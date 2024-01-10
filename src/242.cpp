#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isAnagram(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize != tSize) {
            return retVal;
        }

        unordered_map<char, int> HashTable;
        for (int i = 0; i < sSize; ++i) {
            ++HashTable[s[i]];
            --HashTable[t[i]];
        }
        for (auto [key, value] : HashTable) {
            if (value != 0) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
        string t;
    };
    vector<subject> testData{{"anagram", "nagaram"}, {"rat", "car"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "anagram", t = "nagaram"
     *  Output: true
     *
     *  Input: s = "rat", t = "car"
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = \"" << testData[i].t << "\"\n";

        answer = cSolution.isAnagram(testData[i].s, testData[i].t);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
