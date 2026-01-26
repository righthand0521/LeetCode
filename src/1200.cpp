#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        vector<vector<int>> retVal;

        int arrSize = arr.size();

        sort(arr.begin(), arr.end());
        int minDiff = numeric_limits<int>::max();
        for (int i = 1; i < arrSize; ++i) {
            int diff = arr[i] - arr[i - 1];
            if (diff < minDiff) {
                minDiff = diff;
                retVal.clear();
                retVal.push_back({arr[i - 1], arr[i]});
            } else if (diff == minDiff) {
                retVal.push_back({arr[i - 1], arr[i]});
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{4, 2, 1, 3}}, {{1, 3, 6, 10, 15}}, {{3, 8, -10, 23, 19, -4, -14, 27}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [4,2,1,3]
     *  Output: [[1,2],[2,3],[3,4]]
     *
     *  Input: arr = [1,3,6,10,15]
     *  Output: [[1,3]]
     *
     *  Input: arr = [3,8,-10,23,19,-4,-14,27]
     *  Output: [[-14,-10],[19,23],[23,27]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.minimumAbsDifference(testData[i].arr);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
