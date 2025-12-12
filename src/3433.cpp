#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> retVal(numberOfUsers);

        sort(events.begin(), events.end(), [&](const vector<string>& lth, const vector<string>& rth) {
            bool ret = true;

            int lthTimestamp = stoi(lth[1]);
            int rthTimestamp = stoi(rth[1]);
            if (lthTimestamp != rthTimestamp) {
                ret = (lthTimestamp < rthTimestamp);
            } else if (rth[0] == "OFFLINE") {
                ret = false;
            }

            return ret;
        });

        vector<int> nextOnlineTime(numberOfUsers);
        for (auto&& event : events) {
            int curTime = stoi(event[1]);

            if (event[0] == "MESSAGE") {
                if (event[2] == "ALL") {
                    for (int i = 0; i < numberOfUsers; i++) {
                        retVal[i]++;
                    }
                } else if (event[2] == "HERE") {
                    for (int i = 0; i < numberOfUsers; i++) {
                        if (nextOnlineTime[i] <= curTime) {
                            retVal[i]++;
                        }
                    }
                } else {
                    int event2Size = event[2].size();
                    int idx = 0;
                    for (int i = 0; i < event2Size; i++) {
                        if (isdigit(event[2][i])) {
                            idx = idx * 10 + (event[2][i] - '0');
                        }
                        if ((i + 1 == event2Size) || (event[2][i + 1] == ' ')) {
                            retVal[idx]++;
                            idx = 0;
                        }
                    }
                }
            } else {
                int idx = stoi(event[2]);
                nextOnlineTime[idx] = curTime + 60;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numberOfUsers;
        vector<vector<string>> events;
    };
    vector<subject> testData{{2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "71", "HERE"}}},
                             {2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "12", "ALL"}}},
                             {2, {{"OFFLINE", "10", "0"}, {"MESSAGE", "12", "HERE"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
     *  Output: [2,2]
     *
     *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
     *  Output: [2,2]
     *
     *  Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
     *  Output: [0,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numberOfUsers = " << testData[i].numberOfUsers << ", events = [";
        for (long unsigned int j = 0; j < testData[i].events.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].events[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << testData[i].events[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countMentions(testData[i].numberOfUsers, testData[i].events);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
