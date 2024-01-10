#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestStrChain(vector<string>& words) {
        int retVal = 0;

        unordered_map<string, int> count;

        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            // ascending order
            return a.size() < b.size();
        });
        for (string word : words) {
            count[word] = 1;

            int wordSize = word.size();
            for (int i = 0; i < wordSize; ++i) {
                string previous = word.substr(0, i) + word.substr(i + 1);
                if (count.count(previous)) {
                    count[word] = max(count[word], count[previous] + 1);
                }
            }

            retVal = max(retVal, count[word]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
    };
    vector<subject> testData{
        {{"a", "b", "ba", "bca", "bda", "bdca"}}, {{"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"}}, {{"abcd", "dbqca"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["a","b","ba","bca","bda","bdca"]
     *  Output: 4
     *
     *  Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
     *  Output: 5
     *
     *  Input: words = ["abcd","dbqca"]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.longestStrChain(testData[i].words);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
