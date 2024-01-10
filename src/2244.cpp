#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumRounds(vector<int>& tasks) {
        int retVal = 0;

        sort(tasks.begin(), tasks.end());

        int tasksSize = tasks.size();

        int count = 1;
        for (int i = 1; i < tasksSize; ++i) {
            if (tasks[i] == tasks[i - 1]) {
                ++count;
                continue;
            }

            if (count == 1) {
                retVal = -1;
                return retVal;
            }
            retVal += (count / 3);
            retVal += (count % 3 == 0 ? 0 : 1);

            count = 1;
        }
        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> tasks;
    };
    vector<subject> testData{{{2, 2, 3, 3, 2, 4, 4, 4, 4, 4}}, {{2, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tasks = [2,2,3,3,2,4,4,4,4,4]
     *  Output: 4
     *
     *  Input: tasks = [2,3,3]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tasks = [";
        for (long unsigned int j = 0; j < testData[i].tasks.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].tasks[j];
        }
        cout << "]\n";

        answer = cSolution.minimumRounds(testData[i].tasks);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
