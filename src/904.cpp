#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int totalFruit(vector<int>& fruits) {
        int retVal = 0;

        int fruitsSize = fruits.size();
        /* Example
         *          +--------------------------------------------+-----------------------------+
         *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
         *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
         *          +--------------------------------------------+-------------------------+---|
         *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
         *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
         *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
         *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
         *    head  |                             7              |  max: 2 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                         10 | size: 3 > 2             |   |
         *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         */
        unordered_map<int, int> frequency;
        int frequencySize;
        int head = 0;
        int tail = 0;
        while (tail < fruitsSize) {
            frequency[fruits[tail]]++;
            frequencySize = frequency.size();

            while (frequencySize > 2) {
                frequency[fruits[head]]--;
                if (frequency[fruits[head]] == 0) {
                    frequency.erase(fruits[head]);
                }
                frequencySize = frequency.size();
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            tail++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> fruits;
    };
    vector<subject> testData{{{1, 2, 1}}, {{0, 1, 2, 2}}, {{1, 2, 3, 2, 2}}, {{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: fruits = [1,2,1]
     *  Output: 3
     *
     *  Input: fruits = [0,1,2,2]
     *  Output: 3
     *
     *  Input: fruits = [1,2,3,2,2]
     *  Output: 4
     *
     *  Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: fruits = [";
        for (long unsigned int j = 0; j < testData[i].fruits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].fruits[j];
        }
        cout << "]\n";

        answer = cSolution.totalFruit(testData[i].fruits);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
