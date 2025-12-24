#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int retVal = 0;

        sort(capacity.begin(), capacity.end(), greater<int>());
        int totalApples = accumulate(apple.begin(), apple.end(), 0);
        while (totalApples > 0) {
            totalApples -= capacity[retVal];
            retVal += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> apple;
        vector<int> capacity;
    };
    vector<subject> testData{{{1, 3, 2}, {4, 3, 1, 5, 2}}, {{5, 5, 5}, {2, 4, 2, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: apple = [1,3,2], capacity = [4,3,1,5,2]
     *  Output: 2
     *
     *  Input: apple = [5,5,5], capacity = [2,4,2,7]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: apple = [";
        for (long unsigned int j = 0; j < testData[i].apple.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].apple[j];
        }
        cout << "], capacity = [";
        for (long unsigned int j = 0; j < testData[i].capacity.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].capacity[j];
        }
        cout << "]\n";

        answer = cSolution.minimumBoxes(testData[i].apple, testData[i].capacity);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
