#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> retVal;

        //
        unordered_map<string, int> hashTable;
        for (string word : words) {
            ++hashTable[word];
        }
        auto sortHash = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        };

        //
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(sortHash)> priorityQueue(sortHash);
        for (auto& iterator : hashTable) {
            priorityQueue.emplace(iterator);
            int priorityQueueSize = priorityQueue.size();
            if (priorityQueueSize > k) {
                priorityQueue.pop();
            }
        }
        for (int i = k - 1; i >= 0; i--) {
            retVal.emplace_back(priorityQueue.top().first);
            priorityQueue.pop();
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> words;
        int k;
    };
    vector<subject> testData{{{"i", "love", "leetcode", "i", "love", "coding"}, 2},
                             {{"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: words = ["i","love","leetcode","i","love","coding"], k = 2
     *  Output: ["i","love"]
     *
     *  Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
     *  Output: ["the","is","sunny","day"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].words[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.topKFrequent(testData[i].words, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
