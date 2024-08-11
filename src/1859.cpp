#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    string sortSentence(string s) {
        string retVal = "";

        map<int, string> sMap;
        string tmp = "";
        for (auto c : s) {
            if (isdigit(c)) {
                sMap[c - '0'] = tmp;
                tmp = "";
            } else if (c == ' ') {
                continue;
            } else {
                tmp += c;
            }
        }
        for (auto& iter : sMap) {
            retVal += iter.second;
            retVal += ' ';
        }
        retVal.pop_back();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"is2 sentence4 This1 a3"}, {"Myself2 Me1 I4 and3"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "is2 sentence4 This1 a3"
     *  Output: "This is a sentence"
     *
     *  Input: s = "Myself2 Me1 I4 and3"
     *  Output: "Me Myself and I"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.sortSentence(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
