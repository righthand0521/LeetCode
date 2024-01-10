#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
// key consists of lowercase English letters and ' '.
#define MAX_HASHTABLE (26)
   public:
    string decodeMessage(string key, string message) {
        string pRetVal;

        int HashTableUse = 0;
        vector<char> HashTable(MAX_HASHTABLE, 0);
        for (auto c : key) {
            if (c == ' ') {
                continue;
            }

            if (HashTableUse == MAX_HASHTABLE) {
                break;
            }

            int index = c - 'a';
            if (HashTable[index] == 0) {
                HashTable[index] = HashTableUse + 'a';
                ++HashTableUse;
            }
        }

        for (auto c : message) {
            if (c == ' ') {
                pRetVal.append(1, ' ');
                continue;
            }

            int index = c - 'a';
            pRetVal.append(1, HashTable[index]);
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string key;
        string message;
    };
    vector<subject> testData{{"the quick brown fox jumps over the lazy dog", "vkbs bs t suepuv"},
                             {"eljuxhpwnyrdgtqkviszcfmabo", "zwx hnfx lqantp mnoeius ycgk vcnjrdb"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: key = \"" << testData[i].key << ", message = \"" << testData[i].message << "\"\n";

        answer = cSolution.decodeMessage(testData[i].key, testData[i].message);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
