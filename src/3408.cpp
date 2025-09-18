#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class TaskManager {
   private:
    unordered_map<int, pair<int, int>> taskInfo;
    priority_queue<pair<int, int>> heap;

   public:
    TaskManager(vector<vector<int>> tasks) {
        for (auto& task : tasks) {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            taskInfo[taskId] = {priority, userId};
            heap.emplace(priority, taskId);
        }
    }
    void add(int userId, int taskId, int priority) {
        taskInfo[taskId] = {priority, userId};
        heap.emplace(priority, taskId);
    }
    void edit(int taskId, int newPriority) {
        if (taskInfo.find(taskId) != taskInfo.end()) {
            taskInfo[taskId].first = newPriority;
            heap.emplace(newPriority, taskId);
        }
    }
    void rmv(int taskId) {
        //
        taskInfo.erase(taskId);
    }
    int execTop() {
        int retVal = -1;

        while (heap.empty() == false) {
            auto [priority, taskId] = heap.top();
            heap.pop();
            if (taskInfo.find(taskId) != taskInfo.end() && taskInfo[taskId].first == priority) {
                int userId = taskInfo[taskId].second;
                taskInfo.erase(taskId);
                retVal = userId;
                break;
            }
        }

        return retVal;
    }
};
/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<vector<int>>> val;
    };
    vector<subject> testData{{{"TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"},
                              {{{{1, 101, 10}, {2, 102, 20}, {3, 103, 15}}},
                               {{{4, 104, 5}}},
                               {{{102, 8}}},
                               {},
                               {{{101}}},
                               {{{5, 105, 15}}},
                               {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:
     *  ["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
     *  [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]
     *  Output:
     *  [null, null, null, 3, null, null, 5]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].val[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << "[";
                for (long unsigned int l = 0; l < testData[i].val[j][k].size(); ++l) {
                    cout << (l == 0 ? "" : ", ") << testData[i].val[j][k][l];
                }
                cout << "]";
            }
            cout << "]";
        }
        cout << "]\n";

        TaskManager cTaskManager(testData[i].val[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("TaskManager") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("add") == 0) {
                cTaskManager.add(testData[i].val[j][0][0], testData[i].val[j][0][1], testData[i].val[j][0][2]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("edit") == 0) {
                cTaskManager.edit(testData[i].val[j][0][0], testData[i].val[j][0][1]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("rmv") == 0) {
                cTaskManager.rmv(testData[i].val[j][0][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("execTop") == 0) {
                int retVal = cTaskManager.execTop();
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
