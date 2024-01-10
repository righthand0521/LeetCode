#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    typedef pair<int, double> pid;

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        double retVal = 0;

        vector<vector<pid>> graph(n);
        int edgesSize = edges.size();
        for (int i = 0; i < edgesSize; ++i) {
            int src = edges[i][0];
            int dst = edges[i][1];
            double pathProb = succProb[i];

            graph[src].push_back(pid(dst, pathProb));
            graph[dst].push_back(pid(src, pathProb));
        }

        vector<double> maxProb(n);
        maxProb[start] = 1.0;

        // sort the queue such that the highest probability is at the top
        auto compare = [](const pid& a, const pid& b) { return a.second < b.second; };
        priority_queue<pid, vector<pid>, decltype(compare)> priorityQueue(compare);
        priorityQueue.push(pid(start, 1.0));

        while (priorityQueue.empty() == false) {
            auto [curNode, curProb] = priorityQueue.top();
            priorityQueue.pop();
            if (curNode == end) {
                retVal = curProb;
                break;
            }

            for (pid& next : graph[curNode]) {
                int nxtNode = next.first;
                double pathProb = next.second;
                double nextProb = curProb * pathProb;
                if (nextProb > maxProb[nxtNode]) {
                    maxProb[nxtNode] = nextProb;
                    priorityQueue.push(pid(nxtNode, maxProb[nxtNode]));
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        vector<double> succProb;
        int start;
        int end;
    };
    vector<subject> testData{{3, {{0, 1}, {1, 2}, {0, 2}}, {0.5, 0.5, 0.2}, 0, 2},
                             {3, {{0, 1}, {1, 2}, {0, 2}}, {0.5, 0.5, 0.3}, 0, 2},
                             {3, {{0, 1}}, {0.5}, 0, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
     *  Output: 0.25000
     *
     *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
     *  Output: 0.30000
     *
     *  Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
     *  Output: 0.00000
     */

    Solution cSolution;
    double answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], succProb = [";
        for (long unsigned int j = 0; j < testData[i].succProb.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].succProb[j];
        }
        cout << "], start = " << testData[i].start << ", end = " << testData[i].end << "\n";

        answer = cSolution.maxProbability(testData[i].n, testData[i].edges, testData[i].succProb, testData[i].start,
                                          testData[i].end);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
