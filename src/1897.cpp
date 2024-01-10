#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
// words[i] consists of lowercase English letters.
#define MAX_LETTERS (26)
   public:
    bool makeEqual(vector<string>& words) {
        bool retVal = true;

        int wordsSize = words.size();

        vector<int> hashTable(MAX_LETTERS, 0);
        for (string word : words) {
            for (char c : word) {
                int idx = c - 'a';
                hashTable[idx] += 1;
            }
        }

        for (int value : hashTable) {
            if (value % wordsSize != 0) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        string order;
    };
    vector<subject> testData{{{"abc", "aabc", "bc"}}, {{"ab", "a"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["abc","aabc","bc"]
     *  Output: true
     *
     *  Input: words = ["ab","a"]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].words[j];
        }
        cout << "]\n";

        answer = cSolution.makeEqual(testData[i].words);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
