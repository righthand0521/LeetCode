#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int partitionString(string s) {
        int retVal = 0;

        unordered_map<char, int> hashTable;
        for (auto c : s) {
            if (hashTable[c] == 1) {
                for (auto iterator : hashTable) {
                    hashTable[iterator.first] = 0;
                }
                ++retVal;
            }
            hashTable[c] = 1;
        }
        ++retVal;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abacaba"}, {"ssssss"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abacaba"
     *  Output: 4
     *
     *  Input: s = "ssssss"
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = \"" << testData[i].s << "\"\n";

        answer = cSolution.partitionString(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
