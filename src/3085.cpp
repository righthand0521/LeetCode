#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumDeletions(string word, int k) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (auto &ch : word) {
            frequency[ch]++;
        }

        retVal = word.size();
        for (auto &[_, a] : frequency) {
            int deleted = 0;
            for (auto &[_, b] : frequency) {
                if (a > b) {
                    deleted += b;
                } else if (b > a + k) {
                    deleted += b - (a + k);
                }
            }
            retVal = min(retVal, deleted);
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word;
        int k;
    };
    vector<subject> testData{{"aabcaba", 0}, {"dabdcbdcdcd", 2}, {"aaabaaa", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "aabcaba", k = 0
     *  Output: 3
     *
     *  Input: word = "dabdcbdcdcd", k = 2
     *  Output: 2
     *
     *  Input: word = "aaabaaa", k = 2
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\", k = " << testData[i].k << "\n";

        answer = cSolution.minimumDeletions(testData[i].word, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
