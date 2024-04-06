#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMutation(string start, string end, vector<string>& bank) {
        int retVal = -1;

        int steps = 0;

        // a queue to store each gene string
        queue<string> queue;
        queue.push(start);

        // a hash table to record visited gene string
        unordered_set<string> seen;
        seen.insert(start);

        // Breadth-First Search
        int nodesInQueue;
        string node;
        string neighbor;
        while (!queue.empty()) {
            nodesInQueue = queue.size();
            for (int i = 0; i < nodesInQueue; ++i) {
                node = queue.front();
                queue.pop();
                if (node == end) {
                    retVal = steps;
                    return retVal;
                }

                for (long unsigned j = 0; j < node.size(); ++j) {
                    for (int k = 0; k < 4; ++k) {
                        neighbor = node;
                        // replace the j-th character in neighbor with the k-th character in ACGT
                        neighbor[j] = "ACGT"[k];
                        if ((!seen.count(neighbor)) && (find(bank.begin(), bank.end(), neighbor) != bank.end())) {
                            queue.push(neighbor);
                            seen.insert(neighbor);
                        }
                    }
                }
            }

            ++steps;
        }

        // If there is no such a mutation, return -1.
        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string start;
        string end;
        vector<string> bank;
    };
    vector<subject> testData{{"AACCGGTT", "AACCGGTA", {"AACCGGTA"}},
                             {"AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}},
                             {"AAAAACCC", "AACCCCCC", {"AAAACCCC", "AAACCCCC", "AACCCCCC"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
     *  Output: 1
     *
     *  Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
     *  Output: 2
     *
     *  Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input";
        cout << ": start = " << "\"" << testData[i].start << "\"";
        cout << ", end = " << "\"" << testData[i].end << "\"";
        cout << ", bank = [";
        for (long unsigned int j = 0; j < testData[i].bank.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].bank[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.minMutation(testData[i].start, testData[i].end, testData[i].bank);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
