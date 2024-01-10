#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        string retVal;

        //
        unordered_map<string, string> hashTable;
        for (auto& pKnowledge : knowledge) {
            hashTable[pKnowledge[0]] = pKnowledge[1];
        }

        //
        bool findKey = false;
        string key;
        for (char c : s) {
            if (c == '(') {
                findKey = true;
            } else if (c == ')') {
                if (hashTable.count(key) > 0) {
                    retVal += hashTable[key];
                } else {
                    retVal.push_back('?');
                }
                findKey = false;
                key.clear();
            } else {
                if (findKey == true) {
                    key.push_back(c);
                } else {
                    retVal.push_back(c);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        vector<vector<string>> knowledge;
    };
    vector<subject> testData{{"(name)is(age)yearsold", {{"name", "bob"}, {"age", "two"}}},
                             {"hi(name)", {{"a", "b"}}},
                             {"(a)(a)(a)aaa", {{"a", "yes"}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", knowledge = [";
        for (long unsigned int j = 0; j < testData[i].knowledge.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].knowledge[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].knowledge[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.evaluate(testData[i].s, testData[i].knowledge);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
