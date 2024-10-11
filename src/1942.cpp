#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int retVal = 0;

        int targetArrival = times[targetFriend][0];

        sort(times.begin(), times.end());

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> leavingQueue;
        set<int> availableChairs;
        int nextChair = 0;
        for (auto time : times) {
            int arrival = time[0];
            int leave = time[1];

            while ((leavingQueue.empty() == false) && (leavingQueue.top().first <= arrival)) {
                availableChairs.insert(leavingQueue.top().second);
                leavingQueue.pop();
            }

            int currentChair;
            if (availableChairs.empty() == false) {
                currentChair = *availableChairs.begin();
                availableChairs.erase(availableChairs.begin());
            } else {
                currentChair = nextChair++;
            }

            leavingQueue.push({leave, currentChair});

            if (arrival == targetArrival) {
                retVal = currentChair;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> times;
        int targetFriend;
    };
    vector<subject> testData{{{{1, 4}, {2, 3}, {4, 6}}, 1}, {{{3, 10}, {1, 5}, {2, 6}}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
     *  Output: 1
     *
     *  Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: times = [";
        for (long unsigned int j = 0; j < testData[i].times.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].times[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].times[j][k];
            }
            cout << "]";
        }
        cout << "], targetFriend = " << testData[i].targetFriend << "\n";

        answer = cSolution.smallestChair(testData[i].times, testData[i].targetFriend);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
