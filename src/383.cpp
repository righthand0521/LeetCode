#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // ransomNote and magazine consist of lowercase English letters.
    int letterSize = 26;

   public:
    bool canConstruct(string ransomNote, string magazine) {
        bool retVal = false;

        int ransomNoteSize = ransomNote.size();
        int magazineSize = magazine.size();
        if (ransomNoteSize > magazineSize) {
            return retVal;
        }

        vector<int> hashTable(letterSize, 0);
        for (int i = 0; i < ransomNoteSize; ++i) {
            --hashTable[ransomNote[i] - 'a'];
            ++hashTable[magazine[i] - 'a'];
        }
        for (int i = ransomNoteSize; i < magazineSize; ++i) {
            ++hashTable[magazine[i] - 'a'];
        }

        for (int i = 0; i < letterSize; ++i) {
            if (hashTable[i] < 0) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string ransomNote;
        string magazine;
    };
    vector<subject> testData{{"a", "b"}, {"aa", "ab"}, {"aa", "aab"}, {"ihgg", "ch"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: ransomNote = "a", magazine = "b"
     *  Output: false
     *
     *  Input: ransomNote = "aa", magazine = "ab"
     *  Output: false
     *
     *  Input: ransomNote = "aa", magazine = "aab"
     *  Output: true
     *
     *  Input: ransomNote = "ihgg", magazine = "ch"
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: ransomNote = \"" << testData[i].ransomNote << "\"";
        cout << ", magazine = \"" << testData[i].magazine << "\"\n";

        answer = cSolution.canConstruct(testData[i].ransomNote, testData[i].magazine);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
