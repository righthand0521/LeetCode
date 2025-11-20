#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void help(vector<vector<int>>& intervals, vector<vector<int>>& temp, int pos, int num) {
        for (int i = pos; i >= 0; i--) {
            if (intervals[i][1] < num) {
                break;
            }
            temp[i].emplace_back(num);
        }
    }

   public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int retVal = 0;

        sort(intervals.begin(), intervals.end(), [&](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });

        int intervalsSize = intervals.size();
        vector<vector<int>> temp(intervalsSize);
        for (int i = intervalsSize - 1; i >= 0; i--) {
            int tempSize = temp[i].size();
            for (int j = intervals[i][0], k = tempSize; k < 2; j++, k++) {
                retVal++;
                help(intervals, temp, i - 1, j);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
    };
    vector<subject> testData{
        {{{1, 3}, {3, 7}, {8, 9}}}, {{{1, 3}, {1, 4}, {2, 5}, {3, 5}}}, {{{1, 2}, {2, 3}, {2, 4}, {4, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: intervals = [[1,3],[3,7],[8,9]]
     *  Output: 5
     *
     *  Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
     *  Output: 3
     *
     *  Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: intervals = [";
        for (long unsigned int j = 0; j < testData[i].intervals.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].intervals[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].intervals[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.intersectionSizeTwo(testData[i].intervals);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
