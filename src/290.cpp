#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool wordPattern(string pattern, string s) {
        bool retVal = false;

        vector<string> sList;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            sList.emplace_back(token);
            s.erase(0, pos + delimiter.length());
        }
        sList.emplace_back(s);

        int patternSize = pattern.size();
        int sSize = sList.size();
        if (patternSize != sSize) {
            return retVal;
        }

        unordered_map<char, string> hashTableKey;
        unordered_map<string, char> hashTableVal;
        for (int i = 0; i < patternSize; ++i) {
            if ((hashTableKey.count(pattern[i]) != 0) && (hashTableKey[pattern[i]] != sList[i])) {
                return retVal;
            } else if ((hashTableVal.count(sList[i]) != 0) && (hashTableVal[sList[i]] != pattern[i])) {
                return retVal;
            } else {
                hashTableKey[pattern[i]] = sList[i];
                hashTableVal[sList[i]] = pattern[i];
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string pattern;
        string s;
    };
    vector<subject> testData{{"abba", "dog cat cat dog"},
                             {"abba", "dog cat cat fish"},
                             {"aaaa", "dog cat cat dog"},
                             {"abba", "dog dog dog dog"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pattern = "abba", s = "dog cat cat dog"
     *  Output: true
     *
     *  Input: pattern = "abba", s = "dog cat cat fish"
     *  Output: false
     *
     *  Input: pattern = "aaaa", s = "dog cat cat dog"
     *  Output: false
     *
     *  Input: pattern = "abba", s = "dog dog dog dog"
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pattern = \"" << testData[i].pattern << "\", s = \"" << testData[i].s << "\"\n";

        answer = cSolution.wordPattern(testData[i].pattern, testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
