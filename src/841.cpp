#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
#define BINARY_SEARCH (0)
   public:
    int bfs(vector<vector<int>>& rooms, int enterRoomNumber) {
        int retVal = 0;

        int roomsSize = rooms.size();
        vector<bool> visitedRoom(roomsSize, false);

        queue<int> bfsQueue;
        bfsQueue.emplace(enterRoomNumber);
        visitedRoom[enterRoomNumber] = true;
        retVal += 1;
        while (bfsQueue.empty() == false) {
            auto idx = bfsQueue.front();
            bfsQueue.pop();
            for (auto key : rooms[idx]) {
                if (visitedRoom[key] == true) {
                    continue;
                }
                bfsQueue.emplace(key);
                visitedRoom[key] = true;
                retVal += 1;
            }
        }

        return retVal;
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        bool retVal = false;

        int roomsSize = rooms.size();
        int openedRoomCount = bfs(rooms, 0);
        if (openedRoomCount == roomsSize) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> rooms;
    };
    vector<subject> testData{{{{1}, {2}, {3}, {}}}, {{{1, 3}, {3, 0, 1}, {2}, {0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rooms = [[1],[2],[3],[]]
     *  Output: true
     *
     *  Input: rooms = [[1,3],[3,0,1],[2],[0]]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rooms = [";
        for (long unsigned int j = 0; j < testData[i].rooms.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].rooms[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].rooms[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.canVisitAllRooms(testData[i].rooms);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
