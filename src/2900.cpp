#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        vector<string> retVal;

        retVal.emplace_back(words[0]);
        int groupsSize = groups.size();
        for (int i = 1; i < groupsSize; ++i) {
            if (groups[i] != groups[i - 1]) {
                retVal.emplace_back(words[i]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        vector<int> groups;
    };
    vector<subject> testData{{{"e", "a", "b"}, {0, 0, 1}}, {{"a", "b", "c", "d"}, {1, 0, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["e","a","b"], groups = [0,0,1]
     *  Output: ["e","b"]
     *
     *  Input: words = ["a","b","c","d"], groups = [1,0,1,1]
     *  Output: ["a","b","c"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], groups = [";
        for (long unsigned int j = 0; j < testData[i].groups.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].groups[j];
        }
        cout << "]\n";

        answer = cSolution.getLongestSubsequence(testData[i].words, testData[i].groups);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
