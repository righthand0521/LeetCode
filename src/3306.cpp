#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isVowel(char c) {
        bool retVal = (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');

        return retVal;
    }

   public:
    long long countOfSubstrings(string word, int k) {
        long long retVal = 0;

        int wordSize = word.size();

        vector<int> nextConsonant(wordSize);
        int nextConsonantIndex = wordSize;
        for (int i = wordSize - 1; i >= 0; i--) {
            nextConsonant[i] = nextConsonantIndex;
            if (isVowel(word[i]) == false) {
                nextConsonantIndex = i;
            }
        }

        unordered_map<char, int> vowelCount;
        int consonantCount = 0;
        int start = 0;
        int end = 0;
        while (end < wordSize) {
            char newLetter = word[end];
            if (isVowel(newLetter) == true) {
                vowelCount[newLetter]++;
            } else {
                consonantCount++;
            }

            while (consonantCount > k) {
                char startLetter = word[start];
                if (isVowel(startLetter) == true) {
                    vowelCount[startLetter]--;
                    if (vowelCount[startLetter] == 0) {
                        vowelCount.erase(startLetter);
                    }
                } else {
                    consonantCount--;
                }
                start++;
            }

            while ((start < wordSize) && (vowelCount.size() == 5) && (consonantCount == k)) {
                retVal += nextConsonant[end] - end;
                char startLetter = word[start];
                if (isVowel(startLetter) == true) {
                    vowelCount[startLetter]--;
                    if (vowelCount[startLetter] == 0) {
                        vowelCount.erase(startLetter);
                    }
                } else {
                    consonantCount--;
                }

                start++;
            }

            end++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
        int k;
    };
    vector<subject> testData{{"aeioqq", 1}, {"aeiou", 0}, {"ieaouqqieaouqq", 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "aeioqq", k = 1
     *  Output: 0
     *
     *  Input: word = "aeiou", k = 0
     *  Output: 1
     *
     *  Input: word = "ieaouqqieaouqq", k = 1
     *  Output: 3
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << ", k = " << testData[i].k << "\"\n";

        answer = cSolution.countOfSubstrings(testData[i].word, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
