#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int rearrangeCharacters(string s, string target) {
        int retVal = 0;

        unordered_map<char, int> sHashTable;
        for (char c : s) {
            ++sHashTable[c];
        }

        unordered_map<char, int> targetHashTable;
        for (char c : target) {
            ++targetHashTable[c];
        }

        retVal = max(s.length(), target.length());
        for (auto [key, value] : targetHashTable) {
            retVal = min(retVal, (sHashTable[key] / targetHashTable[key]));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string target;
    };
    vector<subject> testData{{"ilovecodingonleetcode", "code"},
                             {"abcba", "abc"},
                             {"abbaccaddaeea", "aaaaa"},
                             {"abc", "abcd"},
                             {"hshac", "h"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", target = \"" << testData[i].target << "\"\n";

        answer = cSolution.rearrangeCharacters(testData[i].s, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
