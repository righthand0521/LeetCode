#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Graph {
   public:
    vector<vector<pair<int, int>>> adjList;
    Graph(int n, vector<vector<int>>& edges) {
        adjList.resize(n);
        for (auto& e : edges) {
            adjList[e[0]].push_back(make_pair(e[1], e[2]));
        }
    }
    void addEdge(vector<int> edge) {
        //
        adjList[edge[0]].push_back(make_pair(edge[1], edge[2]));
    }
    int shortestPath(int node1, int node2) {
        int retVal = -1;

        int n = adjList.size();
        vector<int> costForNode(n, numeric_limits<int>::max());
        costForNode[node1] = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, node1});
        while (pq.empty() == false) {
            int currCost = pq.top()[0];
            int currNode = pq.top()[1];
            pq.pop();
            if (currCost > costForNode[currNode]) {
                continue;
            }

            if (currNode == node2) {
                retVal = currCost;
                break;
            }

            for (auto& neighbor : adjList[currNode]) {
                int neighborNode = neighbor.first;
                int cost = neighbor.second;
                int newCost = currCost + cost;
                if (newCost < costForNode[neighborNode]) {
                    costForNode[neighborNode] = newCost;
                    pq.push({newCost, neighborNode});
                }
            }
        }

        return retVal;
    }
};
/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<vector<int>>> edges;
        vector<vector<int>> edge;
        vector<vector<int>> node;
    };
    vector<subject> testData{{{"Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"},
                              {{{{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}}}, {{}}, {{}}, {{}}, {{}}},
                              {{}, {}, {}, {1, 3, 4}, {}},
                              {{}, {3, 2}, {0, 3}, {}, {0, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
     *  [[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
     *  Output
     *  [null, 6, -1, null, 6]
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
            if (testData[i].methods[j].compare("Graph") == 0) {
                cout << testData[i].edges[j].size() << ", [";
                for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << "[";
                    for (long unsigned int l = 0; l < testData[i].edges[j][k].size(); ++l) {
                        cout << (l == 0 ? "" : ", ") << testData[i].edges[j][k][l];
                    }
                    cout << "]";
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("shortestPath") == 0) {
                for (long unsigned int k = 0; k < testData[i].node[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << testData[i].node[j][k];
                }
            } else if (testData[i].methods[j].compare("addEdge") == 0) {
                cout << "[";
                for (long unsigned int k = 0; k < testData[i].edge[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << testData[i].edge[j][k];
                }
                cout << "]";
            }
            cout << "]";
        }
        cout << "]\n";

        Graph cGraph(testData[i].edges[0].size(), testData[i].edges[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("Graph") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addEdge") == 0) {
                cGraph.addEdge(testData[i].edge[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("shortestPath") == 0) {
                int retVal = cGraph.shortestPath(testData[i].node[j][0], testData[i].node[j][1]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
