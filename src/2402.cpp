#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        int retVal = 0;

        sort(meetings.begin(), meetings.end());

        vector<long long> roomAvailabilityTime(n, 0);
        vector<int> meetingCount(n, 0);
        for (auto& meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];

            long long minRoomAvailabilityTime = numeric_limits<long long>::max();
            int minAvailableTimeRoom = 0;
            bool foundUnusedRoom = false;

            for (int i = 0; i < n; i++) {
                if (roomAvailabilityTime[i] <= start) {
                    foundUnusedRoom = true;
                    meetingCount[i]++;
                    roomAvailabilityTime[i] = end;
                    break;
                }

                if (minRoomAvailabilityTime > roomAvailabilityTime[i]) {
                    minRoomAvailabilityTime = roomAvailabilityTime[i];
                    minAvailableTimeRoom = i;
                }
            }

            if (foundUnusedRoom == false) {
                roomAvailabilityTime[minAvailableTimeRoom] += end - start;
                meetingCount[minAvailableTimeRoom]++;
            }
        }

        int maxMeetingCount = 0;
        int maxMeetingCountRoom = 0;
        for (int i = 0; i < n; i++) {
            if (meetingCount[i] > maxMeetingCount) {
                maxMeetingCount = meetingCount[i];
                maxMeetingCountRoom = i;
            }
        }
        retVal = maxMeetingCountRoom;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> meetings;
    };
    vector<subject> testData{{2, {{0, 10}, {1, 5}, {2, 7}, {3, 4}}}, {3, {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
     *  Output: 0
     *
     *  Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", meetings = [";
        for (long unsigned int j = 0; j < testData[i].meetings.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].meetings[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].meetings[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.mostBooked(testData[i].n, testData[i].meetings);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
