#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/solutions/510263/java-c-python-priority-queue/
    int maxEvents(vector<vector<int>>& events) {
        int retVal = 0;

        sort(events.begin(), events.end());

        int eventsIndex = 0;
        int eventsSize = events.size();
        int startDay = 0;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        while ((minHeap.size() > 0) || (eventsIndex < eventsSize)) {
            if (minHeap.size() == 0) {
                startDay = events[eventsIndex][0];
            }

            while ((eventsIndex < eventsSize) && (events[eventsIndex][0] <= startDay)) {
                minHeap.push(events[eventsIndex++][1]);
            }

            minHeap.pop();
            ++retVal;
            ++startDay;
            while ((minHeap.size() > 0) && (minHeap.top() < startDay)) {
                minHeap.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> events;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {3, 4}}}, {{{1, 2}, {2, 3}, {3, 4}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: events = [[1,2],[2,3],[3,4]]
     *  Output: 3
     *
     *  Input: events= [[1,2],[2,3],[3,4],[1,2]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: events = [";
        for (long unsigned int j = 0; j < testData[i].events.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].events[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].events[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxEvents(testData[i].events);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
