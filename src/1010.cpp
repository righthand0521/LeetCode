#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto value : time) {
            value %= 60;
            auto iterator = hashTable.find(value);
            if (iterator != hashTable.end()) {
                retVal += hashTable[value];
            }

            value = (60 - value) % 60;
            hashTable[value] += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> time;
    };
    vector<subject> testData{{{30, 20, 150, 100, 40}}, {{60, 60, 60}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: time = [30,20,150,100,40]
     *  IOutput: 3
     *  I
     *  IInput: time = [60,60,60]
     *  IOutput: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: time = [";
        for (long unsigned int j = 0; j < testData[i].time.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].time[j];
        }
        cout << "]\n";

        answer = cSolution.numPairsDivisibleBy60(testData[i].time);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
