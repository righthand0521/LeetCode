#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(const string& departs,
             unordered_map<string, priority_queue<string, vector<string>, std::greater<string>>>& flight,
             vector<string>& retVal) {
        while ((flight.count(departs)) && (flight[departs].size() > 0)) {
            string tmp = flight[departs].top();
            flight[departs].pop();
            dfs(move(tmp), flight, retVal);
        }
        retVal.emplace_back(departs);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> retVal;

        unordered_map<string, priority_queue<string, vector<string>, std::greater<string>>> flight;
        for (auto& iterator : tickets) {
            string departure = iterator[0];
            string arrival = iterator[1];
            flight[departure].emplace(arrival);
        }
        dfs("JFK", flight, retVal);
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<string>> tickets;
    };
    vector<subject> testData{{{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}},
                             {{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
     *  Output: ["JFK","MUC","LHR","SFO","SJC"]
     *
     *  Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
     *  Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
     */

    // Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tickets = [";
        for (long unsigned int j = 0; j < testData[i].tickets.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].tickets[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].tickets[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        Solution cSolution;
        answer = cSolution.findItinerary(testData[i].tickets);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
