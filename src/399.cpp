#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    unordered_map<string, vector<pair<string, double>>> graph;

    double dfs(string src, string dst, unordered_set<string>& visited) {
        double retVal = -1;

        if (graph.find(src) == graph.end()) {
            return retVal;
        }

        if (src == dst) {
            retVal = 1;
            return retVal;
        }

        for (auto node : graph[src]) {
            if (visited.count(node.first)) {
                continue;
            }

            visited.insert(node.first);
            double res = dfs(node.first, dst, visited);
            if (res != -1) {
                retVal = res * node.second;
                return retVal;
            }
        }

        return retVal;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        vector<double> retVal;

        int equationsSize = equations.size();
        for (int i = 0; i < equationsSize; i++) {
            string a = equations[i][0];
            string b = equations[i][1];
            double value = values[i];

            graph[a].push_back({b, value});
            graph[b].push_back({a, (double)1 / value});
        }

        for (auto query : queries) {
            unordered_set<string> visited;
            retVal.push_back(dfs(query[0], query[1], visited));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<string>> equations;
        vector<double> values;
        vector<vector<string>> queries;
    };
    vector<subject> testData{
        {{{"a", "b"}, {"b", "c"}}, {2.0, 3.0}, {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}}},
        {{{"a", "b"}, {"b", "c"}, {"bc", "cd"}}, {1.5, 2.5, 5.0}, {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}}},
        {{{"a", "b"}}, {0.5}, {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
     *  queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
     *  Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
     *
     *  Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
     *  queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
     *  Output: [3.75000,0.40000,5.00000,0.20000]
     *
     *  Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
     *  Output: [0.50000,2.00000,-1.00000,-1.00000]
     */

    // Solution cSolution;
    vector<double> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: equations = [";
        for (long unsigned int j = 0; j < testData[i].equations.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].equations[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].equations[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "], values = [";
        cout.setf(ios::fixed);
        cout.precision(1);
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].values[j];
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].queries[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        Solution cSolution;
        answer = cSolution.calcEquation(testData[i].equations, testData[i].values, testData[i].queries);
        cout << "Output: [";
        cout.setf(ios::fixed);
        cout.precision(5);
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
