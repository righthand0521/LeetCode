#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        vector<int> retVal;

        int deckSize = deck.size();
        queue<int> indexQueue;
        for (int i = 0; i < deckSize; ++i) {
            indexQueue.emplace(i);
        }

        sort(deck.begin(), deck.end());
        retVal.resize(deckSize, 0);
        for (int card : deck) {
            retVal[indexQueue.front()] = card;
            indexQueue.pop();
            if (indexQueue.empty() == false) {
                indexQueue.emplace(indexQueue.front());
                indexQueue.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> deck;
    };
    vector<subject> testData{{{17, 13, 11, 2, 3, 5, 7}}, {{1, 1000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: deck = [17,13,11,2,3,5,7]
     *  Output: [2,13,3,11,5,17,7]
     *
     *  Input: deck = [1,1000]
     *  Output: [1,1000]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: deck = [";
        for (long unsigned int j = 0; j < testData[i].deck.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].deck[j];
        }
        cout << "]\n";

        answer = cSolution.deckRevealedIncreasing(testData[i].deck);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
