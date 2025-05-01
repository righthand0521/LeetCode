#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool check(vector<int>& tasks, vector<int>& workers, int pills, int strength, int middle) {
        bool retVal = false;

        int workersSize = workers.size();
        int workersIdx = workersSize - 1;
        deque<int> workersQueue;
        for (int i = middle - 1; i >= 0; --i) {
            while ((workersIdx >= workersSize - middle) && (workers[workersIdx] + strength >= tasks[i])) {
                workersQueue.push_front(workers[workersIdx]);
                --workersIdx;
            }

            if (workersQueue.empty() == true) {
                return retVal;
            }

            // If the largest element in the deque is greater than or equal to tasks[i]
            if (workersQueue.back() >= tasks[i]) {
                workersQueue.pop_back();
                continue;
            }

            if (pills == 0) {
                return retVal;
            }

            --pills;
            workersQueue.pop_front();
        }
        retVal = true;

        return retVal;
    }

   public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int retVal = 0;

        int tasksSize = tasks.size();
        sort(tasks.begin(), tasks.end());

        int workersSize = workers.size();
        sort(workers.begin(), workers.end());

        int left = 1;
        int right = min(workersSize, tasksSize);
        while (left <= right) {
            int middle = (left + right) / 2;
            if (check(tasks, workers, pills, strength, middle) == true) {
                left = middle + 1;
                retVal = middle;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> tasks;
        vector<int> workers;
        int pills;
        int strength;
    };
    vector<subject> testData{
        {{3, 2, 1}, {0, 3, 3}, 1, 1}, {{5, 4}, {0, 0, 0}, 1, 5}, {{10, 15, 30}, {0, 10, 10, 10, 10}, 3, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
     *  Output: 3
     *
     *  Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
     *  Output: 1
     *
     *  Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tasks = [";
        for (long unsigned int j = 0; j < testData[i].tasks.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].tasks[j];
        }
        cout << ", workers = [";
        for (long unsigned int j = 0; j < testData[i].workers.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].workers[j];
        }
        cout << "], pills = " << testData[i].pills << ", strength = " << testData[i].strength << "\n";

        answer =
            cSolution.maxTaskAssign(testData[i].tasks, testData[i].workers, testData[i].pills, testData[i].strength);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
