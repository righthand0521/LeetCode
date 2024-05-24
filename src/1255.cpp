#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MAX_LETTERS (26)  // words[i], letters[i] contains only lower case English letters.
   private:
    int maxScore;
    vector<int> freq;

    // Check if adding this word exceeds the frequency of any letter
    bool isValidWord(vector<int>& subsetLetters) {
        bool retVal = true;

        for (int c = 0; c < MAX_LETTERS; c++) {
            if (freq[c] < subsetLetters[c]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
    void check(int w, vector<string>& words, vector<int>& score, vector<int>& subsetLetters, int totalScore) {
        if (w == -1) {
            // If all words have been iterated, check the score of this subset
            maxScore = max(maxScore, totalScore);
            return;
        }

        // Not adding words[w] to the current subset
        check(w - 1, words, score, subsetLetters, totalScore);

        // Adding words[w] to the current subset
        int L = words[w].length();
        for (int i = 0; i < L; i++) {
            int c = words[w][i] - 'a';
            subsetLetters[c]++;
            totalScore += score[c];
        }

        if (isValidWord(subsetLetters)) {
            // Consider the next word if this subset is still valid
            check(w - 1, words, score, subsetLetters, totalScore);
        }

        // Rollback effects of this word
        for (int i = 0; i < L; i++) {
            int c = words[w][i] - 'a';
            subsetLetters[c]--;
            totalScore -= score[c];
        }
    }

   public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int retVal = 0;

        maxScore = 0;

        // Count how many times each letter occurs
        freq = vector<int>(MAX_LETTERS, 0);
        for (char c : letters) {
            freq[c - 'a']++;
        }

        int wordsSize = words.size();
        vector<int> subsetLetters = vector<int>(MAX_LETTERS, 0);
        check(wordsSize - 1, words, score, subsetLetters, 0);
        retVal = maxScore;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        vector<char> letters;
        vector<int> score;
    };
    vector<subject> testData{{{"dog", "cat", "dad", "good"},
                              {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'},
                              {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                             {{"xxxz", "ax", "bx", "cx"},
                              {'z', 'a', 'b', 'c', 'x', 'x', 'x'},
                              {4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10}},
                             {{"leetcode"}, {'l', 'e', 't', 'c', 'o', 'd'}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0,
                                                                             0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"],
     *  score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
     *  Output: 23
     *
     *  Input: words = ["xxxz","ax","bx","cx"], letters = ["z","a","b","c","x","x","x"],
     *  score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
     *  Output: 27
     *
     *  Input: words = ["leetcode"], letters = ["l","e","t","c","o","d"],
     *  score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].words[j];
        }
        cout << "], letters = [";
        for (long unsigned int j = 0; j < testData[i].letters.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].letters[j];
        }
        cout << "], score = [";
        for (long unsigned int j = 0; j < testData[i].score.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].score[j];
        }
        cout << "]\n";

        answer = cSolution.maxScoreWords(testData[i].words, testData[i].letters, testData[i].score);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
