#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(string digits, vector<string>& retVal, unordered_map<char, string>& phoneMap, string combination,
                      int index) {
        int digitsSize = digits.size();
        if (index == digitsSize) {
            retVal.emplace_back(combination);
            return;
        }

        for (auto letter : phoneMap[digits[index]]) {
            combination.push_back(letter);
            backtracking(digits, retVal, phoneMap, combination, index + 1);
            combination.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> retVal;

        int digitsSize = digits.size();
        if (digitsSize == 0) {
            return retVal;
        }

        unordered_map<char, string> phoneMap{{'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
                                             {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

        string combination;
        backtracking(digits, retVal, phoneMap, combination, 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string digits;
    };
    vector<subject> testData{{"23"}, {""}, {"2"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: digits = "23"
     *  Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
     *
     *  Input: digits = ""
     *  Output: []
     *
     *  Input: digits = "2"
     *  Output: ["a","b","c"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: digits = \"" << testData[i].digits << "\"\n";

        answer = cSolution.letterCombinations(testData[i].digits);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
