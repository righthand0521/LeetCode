#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canPermutePalindrome(string s) {
        bool retVal = false;

        unordered_map<char, int> hashTable;
        for (char c : s) {
            ++hashTable[c];
        }

        int count = 0;
        for (auto [key, value] : hashTable) {
            if (value % 2 == 1) {
                ++count;
            }
        }
        if (count <= 1) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"code"}, {"aab"}, {"carerac"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.canPermutePalindrome(testData[i].s);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
