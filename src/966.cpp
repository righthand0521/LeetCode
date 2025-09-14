#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    string devowel(const string& word) {
        string retVal;

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (char ch : word) {
            char lower = tolower(ch);
            if (vowels.count(lower)) {
                retVal.push_back('*');
            } else {
                retVal.push_back(lower);
            }
        }

        return retVal;
    }

   public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        vector<string> retVal;

        unordered_set<string> exactSet(wordlist.begin(), wordlist.end());
        unordered_map<string, string> caseMap;
        unordered_map<string, string> vowelMap;
        for (auto& word : wordlist) {
            string lower = word;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (caseMap.count(lower) == 0) {
                caseMap[lower] = word;
            }

            string dv = devowel(word);
            if (vowelMap.count(dv) == 0) {
                vowelMap[dv] = word;
            }
        }

        retVal.reserve(queries.size());
        for (auto& query : queries) {
            if (exactSet.count(query) != 0) {
                retVal.emplace_back(query);
                continue;
            }

            string lowerQuery = query;
            transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
            if (caseMap.count(lowerQuery) != 0) {
                retVal.emplace_back(caseMap[lowerQuery]);
                continue;
            }

            string dvQuery = devowel(query);
            if (vowelMap.count(dvQuery) != 0) {
                retVal.emplace_back(vowelMap[dvQuery]);
            } else {
                retVal.emplace_back("");
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> wordlist;
        vector<string> queries;
    };
    vector<subject> testData{{{"KiTe", "kite", "hare", "Hare"},
                              {"kite", "Kite", "KiTe", "Hare", "HARE", "Hear", "hear", "keti", "keet", "keto"}},
                             {{"yellow"}, {"YellOw"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: wordlist = ["KiTe","kite","hare","Hare"],
     *  queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
     *  Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
     *
     *  Input: wordlist = ["yellow"], queries = ["YellOw"]
     *  Output: ["yellow"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: wordlist = [";
        for (long unsigned int j = 0; j < testData[i].wordlist.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].wordlist[j] << "\"";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].queries[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.spellchecker(testData[i].wordlist, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
