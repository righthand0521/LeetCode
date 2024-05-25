#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    void backtrack(string& s, unordered_set<string>& wordSet, string& currentSentence, vector<string>& results,
                   int startIndex) {
        int sSize = s.size();

        // If we've reached the end of the string, add the current sentence to results
        if (startIndex == sSize) {
            results.push_back(currentSentence);
            return;
        }

        // Iterate over possible end indices
        for (int endIndex = startIndex + 1; endIndex <= sSize; ++endIndex) {
            string word = s.substr(startIndex, endIndex - startIndex);
            // If the word is in the set, proceed with backtracking
            if (wordSet.find(word) != wordSet.end()) {
                string originalSentence = currentSentence;
                if (currentSentence.empty() == false) {
                    currentSentence += " ";
                }
                currentSentence += word;

                // Recursively call backtrack with the new end index
                backtrack(s, wordSet, currentSentence, results, endIndex);

                // Reset currentSentence to its original state
                currentSentence = originalSentence;
            }
        }
    }

   public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> retVal;

        // Convert wordDict to a set for O(1) lookups
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        // Start the backtracking process
        string currentSentence;
        backtrack(s, wordSet, currentSentence, retVal, 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<string> wordDict;
    };
    vector<subject> testData{{"catsanddog", {"cat", "cats", "and", "sand", "dog"}},
                             {"pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"}},
                             {"catsandog", {"cats", "dog", "sand", "and", "cat"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
     *  Output: ["cats and dog","cat sand dog"]
     *
     *  Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
     *  Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
     *
     *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
     *  Output: []
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", wordDict = [";
        for (long unsigned int j = 0; j < testData[i].wordDict.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].wordDict[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.wordBreak(testData[i].s, testData[i].wordDict);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
