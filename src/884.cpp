#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        vector<string> retVal;

        unordered_map<string, int> hashTable;

        string splitStr = "";
        int s1Size = s1.size();
        for (int i = 0; i <= s1Size; ++i) {
            if ((s1[i] != ' ') && (s1[i] != '\0')) {
                splitStr.push_back(s1[i]);
                continue;
            }
            hashTable[splitStr] += 1;
            splitStr = "";
        }
        int s2Size = s2.size();
        for (int i = 0; i <= s2Size; ++i) {
            if ((s2[i] != ' ') && (s2[i] != '\0')) {
                splitStr.push_back(s2[i]);
                continue;
            }
            hashTable[splitStr] += 1;
            splitStr = "";
        }

        for (auto& iterator : hashTable) {
            if (iterator.second == 1) {
                retVal.emplace_back(iterator.first);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s1;
        string s2;
    };
    vector<subject> testData{{"this apple is sweet", "this apple is sour"}, {"apple apple", "banana"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "this apple is sweet", s2 = "this apple is sour"
     *  Output: ["sweet","sour"]
     *
     *  Input: s1 = "apple apple", s2 = "banana"
     *  Output: ["banana"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << ", s2 = \"" << testData[i].s2 << "\"\n";

        answer = cSolution.uncommonFromSentences(testData[i].s1, testData[i].s2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
