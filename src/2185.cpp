#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int prefixCount(vector<string>& words, string pref) {
        int retVal = 0;

        for (string& word : words) {
            if (word.compare(0, pref.size(), pref) == 0) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        string pref;
    };
    vector<subject> testData{{{"pay", "attention", "practice", "attend"}, "at"},
                             {{"leetcode", "win", "loops", "success"}, "code"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["pay","attention","practice","attend"], pref = "at"
     *  Output: 2
     *
     *  Input: words = ["leetcode","win","loops","success"], pref = "code"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "], pref = \"" << testData[i].pref << "\"\n ";

        answer = cSolution.prefixCount(testData[i].words, testData[i].pref);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
