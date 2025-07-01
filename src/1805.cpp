#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int numDifferentIntegers(string word) {
        int retVal = 0;

        unordered_set<string> hashTable;

        int wordSize = word.size();
        int left = 0;
        while (true) {
            while ((left < wordSize) && (isdigit(word[left]) == false)) {
                left++;
            }
            if (left == wordSize) {
                break;
            }

            int right = left;
            while ((right < wordSize) && (isdigit(word[right]) == true)) {
                right++;
            }

            while ((right - left > 1) && (word[left] == '0')) {
                left++;
            }
            hashTable.insert(word.substr(left, right - left));

            left = right;
        }

        retVal = hashTable.size();

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"a123bc34d8ef34"}, {"leet1234code234"}, {"a1b01c001"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "a123bc34d8ef34"
     *  Output: 3
     *
     *  Input: word = "leet1234code234"
     *  Output: 2
     *
     *  Input: word = "a1b01c001"
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.numDifferentIntegers(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
