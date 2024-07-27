#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    // source, target consist of lowercase English letters.
    // original[i], changed[i] are lowercase English letters.
    int letters = 26;

    vector<long long> dijkstra(int startChar, const vector<vector<pair<int, int>>>& adjacencyList) {
        vector<long long> retVal(letters, -1);

        // Priority queue to store characters with their conversion cost, sorted by cost
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> priorityQueue;
        priorityQueue.push({0, startChar});
        while (priorityQueue.empty() == false) {
            auto [currentCost, currentChar] = priorityQueue.top();
            priorityQueue.pop();

            if ((retVal[currentChar] != -1) && (retVal[currentChar] < currentCost)) {
                continue;
            }

            // Explore all possible conversions from the current character
            for (auto& [targetChar, conversionCost] : adjacencyList[currentChar]) {
                long long newTotalCost = currentCost + conversionCost;

                // If we found a cheaper conversion, update its cost
                if ((retVal[targetChar] == -1) || (newTotalCost < retVal[targetChar])) {
                    retVal[targetChar] = newTotalCost;
                    priorityQueue.push({newTotalCost, targetChar});
                }
            }
        }

        return retVal;
    }

   public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
        long long retVal = 0;

        vector<vector<pair<int, int>>> adjacencyList(letters);
        int originalSize = original.size();
        for (int i = 0; i < originalSize; i++) {
            adjacencyList[original[i] - 'a'].push_back({changed[i] - 'a', cost[i]});
        }

        vector<vector<long long>> minConversionCosts(26, vector<long long>(letters));
        for (int i = 0; i < letters; i++) {
            minConversionCosts[i] = dijkstra(i, adjacencyList);
        }

        int sourceSize = source.length();
        for (int i = 0; i < sourceSize; i++) {
            if (source[i] != target[i]) {
                long long charConversionCost = minConversionCosts[source[i] - 'a'][target[i] - 'a'];
                if (charConversionCost == -1) {
                    retVal = -1;  // If it is impossible to convert source to target, return -1.
                    return retVal;
                }
                retVal += charConversionCost;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string source;
        string target;
        vector<char> original;
        vector<char> changed;
        vector<int> cost;
    };
    vector<subject> testData{
        {"abcd", "acbe", {'a', 'b', 'c', 'c', 'e', 'd'}, {'b', 'c', 'b', 'e', 'b', 'e'}, {2, 5, 5, 1, 2, 20}},
        {"aaaa", "bbbb", {'a', 'c'}, {'c', 'b'}, {1, 2}},
        {"abcd", "abce", {'a'}, {'e'}, {10000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: source = "abcd", target = "acbe",
     *  original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
     *  Output: 28
     *
     *  Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
     *  Output: 12
     *
     *  Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
     *  Output: -1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: source = \"" << testData[i].source << "\", target = \"" << testData[i].target << "\"";
        cout << ", original = [";
        for (long unsigned int j = 0; j < testData[i].original.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].original[j] << "\"";
        }
        cout << "], changed = [";
        for (long unsigned int j = 0; j < testData[i].changed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].changed[j] << "\"";
        }
        cout << "], cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cost[j];
        }
        cout << "]\n";

        answer = cSolution.minimumCost(testData[i].source, testData[i].target, testData[i].original,
                                       testData[i].changed, testData[i].cost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
