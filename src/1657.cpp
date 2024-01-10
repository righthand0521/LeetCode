#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool closeStrings(string word1, string word2) {
        bool retVal = false;

        int word1Size = word1.size();
        int word2Size = word2.size();
        if (word1Size != word2Size) {
            return retVal;
        }

#define HASHTABLE_SIZE (26)  // word1 and word2 contain only lowercase English letters.
        vector<int> hashTable1(HASHTABLE_SIZE, 0);
        vector<int> hashTable2(HASHTABLE_SIZE, 0);
        for (int i = 0; i < word1Size; ++i) {
            hashTable1[word1[i] - 'a']++;
            hashTable2[word2[i] - 'a']++;
        }

        for (int i = 0; i < HASHTABLE_SIZE; ++i) {
            if ((hashTable1[i] == 0) && (hashTable2[i] != 0)) {
                return retVal;
            } else if ((hashTable1[i] != 0) && (hashTable2[i] == 0)) {
                return retVal;
            }
        }

        sort(hashTable1.begin(), hashTable1.end());
        sort(hashTable2.begin(), hashTable2.end());
        if (hashTable1 != hashTable2) {
            return retVal;
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word1;
        string word2;
    };
    vector<subject> testData{{"abc", "bca"}, {"a", "aa"}, {"cabbba", "abbccc"}, {"uau", "ssx"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word1 = "abc", word2 = "bca"
     *  Output: true
     *
     *  Input: word1 = "a", word2 = "aa"
     *  Output: false
     *
     *  Input: word1 = "cabbba", word2 = "abbccc"
     *  Output: true
     *
     *  Input: word1 = "uau", word2 = "ssx"
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word1 = \"" << testData[i].word1 << "\", word2 = \"" << testData[i].word2 << "\"\n";

        answer = cSolution.closeStrings(testData[i].word1, testData[i].word2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
