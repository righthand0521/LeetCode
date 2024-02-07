#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string frequencySort(string s) {
        string retVal;

        unordered_map<char, int> hashTable;
        for (auto &c : s) {
            hashTable[c]++;
        }

        vector<pair<char, int>> sortHashTable;
        for (auto &iterator : hashTable) {
            sortHashTable.emplace_back(iterator);
        }
        sort(sortHashTable.begin(), sortHashTable.end(),
             [](const pair<char, int> &a, const pair<char, int> &b) { return a.second > b.second; });

        for (auto &iterator : sortHashTable) {
            for (int i = 0; i < iterator.second; ++i) {
                retVal.push_back(iterator.first);
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"tree"}, {"cccaaa"}, {"Aabb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "tree"
     *  Output: "eert"
     *
     *  Input: s = "cccaaa"
     *  Output: "aaaccc"
     *
     *  Input: s = "Aabb"
     *  Output: "bbAa"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.frequencySort(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
