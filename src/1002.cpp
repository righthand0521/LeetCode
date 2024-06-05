#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    int letters = 26;  // words[i] consists of lowercase English letters.

   public:
    vector<string> commonChars(vector<string>& words) {
        vector<string> retVal;

        vector<int> minFrequency(letters, numeric_limits<int>::max());
        for (string word : words) {
            vector<int> frequency(letters, 0);
            for (char c : word) {
                int idx = c - 'a';
                frequency[idx] += 1;
            }
            for (int i = 0; i < letters; ++i) {
                minFrequency[i] = min(minFrequency[i], frequency[i]);
            }
        }

        for (int i = 0; i < letters; ++i) {
            for (int j = 0; j < minFrequency[i]; ++j) {
                retVal.emplace_back(1, i + 'a');
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{{{"bella", "label", "roller"}}, {{"cool", "lock", "cook"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["bella","label","roller"]
     *  Output: ["e","l","l"]
     *
     *  Input: words = ["cool","lock","cook"]
     *  Output: ["c","o"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.commonChars(testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
