#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countCharacters(vector<string>& words, string chars) {
        int retVal = 0;

        // words[i] and chars consist of lowercase English letters.
        vector<int> charsCount(26, 0);
        for (char c : chars) {
            int idx = c - 'a';
            charsCount[idx]++;
        }

        vector<int> check;
        for (string word : words) {
            check.assign(charsCount.begin(), charsCount.end());
            int count = 0;
            for (char c : word) {
                int idx = c - 'a';
                if (check[idx] == 0) {
                    break;
                }
                check[idx]--;
                count++;
            }

            int wordSize = word.size();
            if (count == wordSize) {
                retVal += count;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        string chars;
    };
    vector<subject> testData{{{"cat", "bt", "hat", "tree"}, "atach"},
                             {{"hello", "world", "leetcode"}, "welldonehoneyr"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["cat","bt","hat","tree"], chars = "atach"
     *  Output: 6
     *
     *  Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], chars = \"" << testData[i].chars << "\"\n";

        answer = cSolution.countCharacters(testData[i].words, testData[i].chars);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
