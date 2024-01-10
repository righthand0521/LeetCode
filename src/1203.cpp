#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> topologicalSort(vector<int>& degree, vector<vector<int>>& graph, vector<int>& items) {
        vector<int> retVal;

        queue<int> recordQueue;
        for (auto& item : items) {
            if (degree[item] == 0) {
                recordQueue.push(item);
            }
        }

        vector<int> visited;
        while (recordQueue.empty() == false) {
            int u = recordQueue.front();
            recordQueue.pop();
            visited.emplace_back(u);

            for (auto& v : graph[u]) {
                if (--degree[v] == 0) {
                    recordQueue.push(v);
                }
            }
        }
        if (visited.size() == items.size()) {
            retVal = visited;
        }

        return retVal;
    }
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<int> retVal;

        vector<int> id;
        for (int i = 0; i < n + m; ++i) {
            id.emplace_back(i);
        }

        vector<vector<int>> groupItem(n + m);
        int leftId = m;
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                group[i] = leftId;
                leftId += 1;
            }
            groupItem[group[i]].emplace_back(i);
        }

        vector<vector<int>> groupGraph(n + m);
        vector<int> groupDegree(n + m, 0);
        vector<vector<int>> itemGraph(n);
        vector<int> itemDegree(n, 0);
        for (int i = 0; i < n; ++i) {
            int curGroupId = group[i];
            for (auto& item : beforeItems[i]) {
                int beforeGroupId = group[item];
                if (beforeGroupId == curGroupId) {
                    itemDegree[i] += 1;
                    itemGraph[item].emplace_back(i);
                } else {
                    groupDegree[curGroupId] += 1;
                    groupGraph[beforeGroupId].emplace_back(curGroupId);
                }
            }
        }

        vector<int> groupTopSort = topologicalSort(groupDegree, groupGraph, id);
        if (groupTopSort.size() == 0) {
            return retVal;
        }

        for (auto& curGroupId : groupTopSort) {
            int size = groupItem[curGroupId].size();
            if (size == 0) {
                continue;
            }

            vector<int> res = topologicalSort(itemDegree, itemGraph, groupItem[curGroupId]);
            if (res.size() == 0) {
                return retVal;
            }

            for (auto& item : res) {
                retVal.emplace_back(item);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
        vector<int> group;
        vector<vector<int>> beforeItems;
    };
    vector<subject> testData{{8, 2, {-1, -1, 1, 0, 0, 1, 0, -1}, {{}, {6}, {5}, {6}, {3, 6}, {}, {}, {}}},
                             {8, 2, {-1, -1, 1, 0, 0, 1, 0, -1}, {{}, {6}, {5}, {6}, {3}, {}, {4}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
     *  Output: [6,3,4,1,5,2,0,7]
     *
     *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << ", group = [";
        for (long unsigned int j = 0; j < testData[i].group.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].group[j];
        }
        cout << "], beforeItems = [";
        for (long unsigned int j = 0; j < testData[i].beforeItems.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].beforeItems[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].beforeItems[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.sortItems(testData[i].n, testData[i].m, testData[i].group, testData[i].beforeItems);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
