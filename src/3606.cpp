#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool check(string code, bool isActive) {
        bool retVal = isActive;

        for (auto it : code) {
            if ((it != '_') && (isalnum(it) == 0)) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }

   public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        vector<string> retVal;

        vector<string> groups[4];
        int codeSize = code.size();
        for (int i = 0; i < codeSize; i++) {
            int len = code[i].size();
            if (len == 0) {
                continue;
            } else if (check(code[i], isActive[i]) == false) {
                continue;
            }

            if (businessLine[i] == "electronics") {
                groups[0].emplace_back(code[i]);
            } else if (businessLine[i] == "grocery") {
                groups[1].emplace_back(code[i]);
            } else if (businessLine[i] == "pharmacy") {
                groups[2].emplace_back(code[i]);
            } else if (businessLine[i] == "restaurant") {
                groups[3].emplace_back(code[i]);
            }
        }
        for (auto& group : groups) {
            sort(group.begin(), group.end());
            retVal.insert(retVal.end(), group.begin(), group.end());
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> code;
        vector<string> businessLine;
        vector<bool> isActive;
    };
    vector<subject> testData{
        {{"SAVE20", "", "PHARMA5", "SAVE@20"},
         {"restaurant", "grocery", "pharmacy", "restaurant"},
         {true, true, true, true}},
        {{"GROCERY15", "ELECTRONICS_50", "DISCOUNT10"}, {"grocery", "electronics", "invalid"}, {false, true, true}}};

    int numberOfTestCase = testData.size();
    /* Example
     *  Input: code = ["SAVE20","","PHARMA5","SAVE@20"],
     *         businessLine = ["restaurant","grocery","pharmacy","restaurant"],
     *         isActive = [true,true,true,true]
     *  Output: ["PHARMA5","SAVE20"]
     *
     *  Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"],
     *         businessLine = ["grocery","electronics","invalid"],
     *         isActive = [false,true,true]
     *  Output: ["ELECTRONICS_50"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: code = [";
        for (long unsigned int j = 0; j < testData[i].code.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].code[j] << "\"";
        }
        cout << "], businessLine = [";
        for (long unsigned int j = 0; j < testData[i].businessLine.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].businessLine[j] << "\"";
        }
        cout << "], isActive = [";
        for (long unsigned int j = 0; j < testData[i].isActive.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (testData[i].isActive[j] ? "true" : "false");
        }
        cout << "]\n";

        answer = cSolution.validateCoupons(testData[i].code, testData[i].businessLine, testData[i].isActive);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "\"" << answer[j] << "\"";
        }
        cout << "]";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
