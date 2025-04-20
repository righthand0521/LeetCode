#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numRabbits(vector<int>& answers) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int answer : answers) {
            ++hashTable[answer];
        }

        for (auto& [answer, count] : hashTable) {
            retVal += ((count + answer) / (answer + 1) * (answer + 1));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> answers;
    };
    vector<subject> testData{{{1, 1, 2}}, {{10, 10, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: answers = [1,1,2]
     *  Output: 5
     *
     *  Input: answers = [10,10,10]
     *  Output: 11
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: answers = [";
        for (long unsigned int j = 0; j < testData[i].answers.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].answers[j];
        }
        cout << "]\n";

        answer = cSolution.numRabbits(testData[i].answers);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
