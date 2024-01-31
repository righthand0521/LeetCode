#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> retVal;

        unordered_map<string, vector<string>> hashTable;
        for (string str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            hashTable[key].emplace_back(str);
        }

        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            retVal.emplace_back(iterator->second);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
    };
    vector<subject> testData{{{"eat", "tea", "tan", "ate", "nat", "bat"}}, {{""}}, {{"a"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["eat","tea","tan","ate","nat","bat"]
     *  Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
     *
     *  Input: strs = [""]
     *  Output: [[""]]
     *
     *  Input: strs = ["a"]
     *  Output: [["a"]]
     */

    Solution cSolution;
    vector<vector<string>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.groupAnagrams(testData[i].strs);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << answer[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
