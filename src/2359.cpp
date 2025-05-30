#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(int node, vector<int>& edges, vector<int>& dist, vector<bool>& visit) {
        visit[node] = true;

        int neighbor = edges[node];
        if ((neighbor != -1) && (visit[neighbor] == false)) {
            dist[neighbor] = 1 + dist[node];
            dfs(neighbor, edges, dist, visit);
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int retVal = -1;

        int edgesSize = edges.size();

        vector<int> dist1(edgesSize, numeric_limits<int>::max());
        dist1[node1] = 0;
        vector<bool> visit1(edgesSize, false);
        dfs(node1, edges, dist1, visit1);

        vector<int> dist2(edgesSize, numeric_limits<int>::max());
        dist2[node2] = 0;
        vector<bool> visit2(edgesSize, false);
        dfs(node2, edges, dist2, visit2);

        int minDist = numeric_limits<int>::max();
        for (int currNode = 0; currNode < edgesSize; ++currNode) {
            if (minDist > max(dist1[currNode], dist2[currNode])) {
                retVal = currNode;
                minDist = max(dist1[currNode], dist2[currNode]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> edges;
        int node1;
        int node2;
    };
    vector<subject> testData{{{2, 2, 3, -1}, 0, 1}, {{1, 2, -1}, 0, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
     *  Output: 2
     *
     *  Input: edges = [1,2,-1], node1 = 0, node2 = 2
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].edges[j];
        }
        cout << "], node1 = " << testData[i].node1 << ", node2 = " << testData[i].node2 << "\n";

        answer = cSolution.closestMeetingNode(testData[i].edges, testData[i].node1, testData[i].node2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
