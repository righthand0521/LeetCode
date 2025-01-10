#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int letter = 26;
    vector<int> count(string word) {
        vector<int> retVal(letter, 0);

        for (char c : word) {
            retVal[c - 'a'] += 1;
        }

        return retVal;
    }

   public:
    vector<string> wordSubsets(vector<string> &words1, vector<string> &words2) {
        vector<string> retVal;

        vector<int> bmax(letter, 0);
        for (string word : words2) {
            vector<int> countResult = count(word);
            for (int i = 0; i < letter; ++i) {
                bmax[i] = max(bmax[i], countResult[i]);
            }
        }

        for (string word : words1) {
            vector<int> countResult = count(word);
            int i;
            for (i = 0; i < letter; ++i) {
                int x = countResult[i];
                int y = bmax[i];
                if (x < y) {
                    break;
                }
            }
            if (i == letter) {
                retVal.emplace_back(word);
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<string> words1;
        vector<string> words2;
    };
    vector<subject> testData{{{"amazon", "apple", "facebook", "google", "leetcode"}, {"e", "o"}},
                             {{"amazon", "apple", "facebook", "google", "leetcode"}, {"l", "e"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
     *  Output: ["facebook","google","leetcode"]
     *
     *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
     *  Output: ["apple","google","leetcode"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words1 = [";
        for (long unsigned int j = 0; j < testData[i].words1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words1[j] << "\"";
        }
        cout << "], words2 = [";
        for (long unsigned int j = 0; j < testData[i].words2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words2[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.wordSubsets(testData[i].words1, testData[i].words2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
