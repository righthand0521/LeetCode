#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int leastInterval(vector<char>& tasks, int n) {
        int retVal = 0;

        int tasksSize = tasks.size();

        vector<int> frequency(26, 0);
        int maxFrequency = 0;
        for (char task : tasks) {
            int idx = task - 'A';
            frequency[idx]++;
            maxFrequency = max(maxFrequency, frequency[idx]);
        }

        int time = (maxFrequency - 1) * (n + 1);
        for (int f : frequency) {
            if (f == maxFrequency) {
                time++;
            }
        }

        retVal = max(tasksSize, time);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<char> tasks;
        int n;
    };
    vector<subject> testData{
        {{'A', 'A', 'A', 'B', 'B', 'B'}, 2}, {{'A', 'C', 'A', 'B', 'D', 'B'}, 1}, {{'A', 'A', 'A', 'B', 'B', 'B'}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tasks = ["A","A","A","B","B","B"], n = 2
     *  Output: 8
     *
     *  Input: tasks = ["A","C","A","B","D","B"], n = 1
     *  Output: 6
     *
     *  Input: tasks = ["A","A","A", "B","B","B"], n = 3
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tasks = [";
        for (long unsigned int j = 0; j < testData[i].tasks.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].tasks[j] << "\"";
        }
        cout << "], n = " << testData[i].n << "\n";

        answer = cSolution.leastInterval(testData[i].tasks, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
