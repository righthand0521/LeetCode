#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canReach(vector<int>& arr, int start) {
        bool retVal = false;

        int len = arr.size();

        // Breadth-First Search
        queue<int> bfsQueue;
        bfsQueue.push(start);

        vector<bool> visit(len);
        visit[start] = true;

        int key;
        while (bfsQueue.empty() == false) {
            int idx = bfsQueue.front();
            bfsQueue.pop();

            if (arr[idx] == 0) {
                retVal = true;
                return retVal;
            }

            key = idx + arr[idx];
            if ((key < len) && (visit[key] == false)) {
                visit[key] = true;
                bfsQueue.push(key);
            }

            key = idx - arr[idx];
            if ((key >= 0) && (visit[key] == false)) {
                visit[key] = true;
                bfsQueue.push(key);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int start;
    };
    vector<subject> testData{{{4, 2, 3, 0, 3, 1, 2}, 5}, {{4, 2, 3, 0, 3, 1, 2}, 0}, {{3, 0, 2, 1, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [4,2,3,0,3,1,2], start = 5
     *  Output: true
     *
     *  Input: arr = [4,2,3,0,3,1,2], start = 0
     *  Output: true
     *
     *  Input: arr = [3,0,2,1,2], start = 2
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "], start = " << testData[i].start << "\n";

        answer = cSolution.canReach(testData[i].arr, testData[i].start);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
