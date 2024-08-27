#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    unordered_map<string, int> wordId;
    vector<vector<int>> edge;
    int nodeNum = 0;

    void addWord(string& word) {
        if (wordId.count(word) == 0) {
            wordId[word] = nodeNum++;
            edge.emplace_back();
        }
    }
    void addEdge(string& word) {
        addWord(word);

        int id1 = wordId[word];
        for (char& it : word) {
            char tmp = it;

            it = '*';
            addWord(word);

            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);

            it = tmp;
        }
    }

   public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int retVal = 0;

        wordId.clear();
        edge.clear();
        nodeNum = 0;

        for (string& word : wordList) {
            addEdge(word);
        }

        addEdge(beginWord);
        if (wordId.count(endWord) == 0) {
            return retVal;
        }

        int beginId = wordId[beginWord];
        int endId = wordId[endWord];

        vector<int> distance(nodeNum, numeric_limits<int>::max());
        distance[beginId] = 0;

        queue<int> bfsQueue;
        bfsQueue.push(beginId);
        while (bfsQueue.empty() == false) {
            int x = bfsQueue.front();
            bfsQueue.pop();
            if (x == endId) {
                retVal = distance[endId] / 2 + 1;
                break;
            }

            for (int& it : edge[x]) {
                if (distance[it] == numeric_limits<int>::max()) {
                    distance[it] = distance[x] + 1;
                    bfsQueue.push(it);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string beginWord;
        string endWord;
        vector<string> wordList;
    };
    vector<subject> testData{{"hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}},
                             {"hit", "cog", {"hot", "dot", "dog", "lot", "log"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
     *  Output: 5
     *
     *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: beginWord = \"" << testData[i].beginWord << "\", ";
        cout << "endWord = \"" << testData[i].endWord << "\", ";
        cout << "wordList = [";
        for (long unsigned int j = 0; j < testData[i].wordList.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].wordList[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.ladderLength(testData[i].beginWord, testData[i].endWord, testData[i].wordList);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
