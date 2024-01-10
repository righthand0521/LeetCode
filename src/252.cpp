#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        bool retVal = true;

#if (1)  // C++ sort function automatically sorts a vector first by the 1st element, then by the 2nd element and so on.
        sort(intervals.begin(), intervals.end());
#else
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
#endif

        for (long unsigned int i = 1; i < intervals.size(); ++i) {
            if (intervals[i - 1][1] > intervals[i][0]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
    };
    vector<subject> testData{{{{0, 30}, {5, 10}, {15, 20}}}, {{{7, 10}, {2, 4}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer = false;
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

        answer = cSolution.canAttendMeetings(testData[i].intervals);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
