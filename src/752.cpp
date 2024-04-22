#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<char, char> nextSlot = {{'0', '1'}, {'1', '2'}, {'2', '3'}, {'3', '4'}, {'4', '5'},
                                          {'5', '6'}, {'6', '7'}, {'7', '8'}, {'8', '9'}, {'9', '0'}};
    unordered_map<char, char> prevSlot = {{'0', '9'}, {'1', '0'}, {'2', '1'}, {'3', '2'}, {'4', '3'},
                                          {'5', '4'}, {'6', '5'}, {'7', '6'}, {'8', '7'}, {'9', '8'}};

   public:
    int openLock(vector<string>& deadends, string target) {
        int retVal = -1;

        unordered_set<string> visitedCombinations(deadends.begin(), deadends.end());
        if (visitedCombinations.find("0000") != visitedCombinations.end()) {
            return retVal;
        }
        visitedCombinations.insert("0000");

        retVal = 0;
        queue<string> pendingCombinations;
        pendingCombinations.push("0000");
        while (pendingCombinations.empty() == false) {
            for (int currLevelNodesCount = pendingCombinations.size(); currLevelNodesCount > 0; --currLevelNodesCount) {
                string currentCombination = pendingCombinations.front();
                pendingCombinations.pop();
                if (currentCombination == target) {
                    return retVal;
                }

                for (int wheel = 0; wheel < 4; wheel += 1) {
                    string newCombination = currentCombination;
                    newCombination[wheel] = nextSlot[newCombination[wheel]];
                    if (visitedCombinations.find(newCombination) == visitedCombinations.end()) {
                        pendingCombinations.push(newCombination);
                        visitedCombinations.insert(newCombination);
                    }

                    newCombination = currentCombination;
                    newCombination[wheel] = prevSlot[newCombination[wheel]];
                    if (visitedCombinations.find(newCombination) == visitedCombinations.end()) {
                        pendingCombinations.push(newCombination);
                        visitedCombinations.insert(newCombination);
                    }
                }
            }
            retVal += 1;
        }
        retVal = -1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> deadends;
        string target;
    };
    vector<subject> testData{{{"0201", "0101", "0102", "1212", "2002"}, "0202"},
                             {{"8888"}, "0009"},
                             {{"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"}, "8888"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
     *  Output: 6
     *
     *  Input: deadends = ["8888"], target = "0009"
     *  Output: 1
     *
     *  Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
     *  Output: -1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: deadends = [";
        for (long unsigned int j = 0; j < testData[i].deadends.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].deadends[j] << "\"";
        }
        cout << "], target = \"" << testData[i].target << "\"\n";

        answer = cSolution.openLock(testData[i].deadends, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
