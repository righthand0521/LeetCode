#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int retVal = -1;

        vector<int> record(time, 0);
        for (auto iterator : clips) {
            int start = iterator[0];
            int end = iterator[1];
            if (start < time) {
                record[start] = max(record[start], end);
            }
        }

        retVal = 0;
        int lastEnd = 0;
        int previousEnd = 0;
        for (int i = 0; i < time; ++i) {
            lastEnd = max(lastEnd, record[i]);
            if (i == lastEnd) {
                retVal = -1;
                break;
            } else if (i == previousEnd) {
                retVal += 1;
                previousEnd = lastEnd;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> clips;
        int time;
    };
    vector<subject> testData{{{{0, 2}, {4, 6}, {8, 10}, {1, 9}, {1, 5}, {5, 9}}, 10},
                             {{{0, 1}, {1, 2}}, 5},
                             {{{0, 1},
                               {6, 8},
                               {0, 2},
                               {5, 6},
                               {0, 4},
                               {0, 3},
                               {6, 7},
                               {1, 3},
                               {4, 7},
                               {1, 4},
                               {2, 5},
                               {2, 6},
                               {3, 4},
                               {4, 5},
                               {5, 7},
                               {6, 9}},
                              9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
     *  Output: 3
     *
     *  Input: clips = [[0,1],[1,2]], time = 5
     *  Output: -1
     *
     *  Input: clips =
     *  [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: clips = [";
        for (long unsigned int j = 0; j < testData[i].clips.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].clips[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].clips[j][k];
            }
            cout << "]";
        }
        cout << "], time = " << testData[i].time << "\n";

        answer = cSolution.videoStitching(testData[i].clips, testData[i].time);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
