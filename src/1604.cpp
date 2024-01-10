#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        vector<string> retVal;

        int len = keyName.size();

        unordered_map<string, vector<int>> hashTable;
        for (int i = 0; i < len; ++i) {
            int hour = (keyTime[i][0] - '0') * 10 + (keyTime[i][1] - '0');
            int minute = (keyTime[i][3] - '0') * 10 + (keyTime[i][4] - '0');
            hashTable[keyName[i]].emplace_back(hour * 60 + minute);
        }

        for (auto& [pName, pTime] : hashTable) {
            sort(pTime.begin(), pTime.end());

            for (long unsigned int i = 2; i < pTime.size(); ++i) {
                if (pTime[i] - pTime[i - 2] <= 60) {
                    retVal.emplace_back(pName);
                    break;
                }
            }
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> keyName;
        vector<string> keyTime;
    };
    vector<subject> testData{{{"daniel", "daniel", "daniel", "luis", "luis", "luis", "luis"},
                              {"10:00", "10:40", "11:00", "09:00", "11:00", "13:00", "15:00"}},
                             {{"alice", "alice", "alice", "bob", "bob", "bob", "bob"},
                              {"12:01", "12:00", "18:00", "21:00", "21:20", "21:30", "23:00"}},
                             {{"john", "john", "john"}, {"23:58", "23:59", "00:01"}},
                             {{"leslie", "leslie", "leslie", "clare", "clare", "clare", "clare"},
                              {"13:00", "13:20", "14:00", "18:00", "18:51", "19:30", "19:49"}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: keyName = [";
        for (long unsigned int j = 0; j < testData[i].keyName.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].keyName[j] << "\"";
        }
        cout << "], keyTime = [";
        for (long unsigned int j = 0; j < testData[i].keyTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].keyTime[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.alertNames(testData[i].keyName, testData[i].keyTime);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
