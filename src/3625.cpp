#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int countTrapezoids(vector<vector<int>>& points) {
        int retVal = 0;

        int pointsSize = points.size();
        int inf = 1e9 + 7;

        unordered_map<float, vector<float>> slopeToIntercept;
        unordered_map<int, vector<float>> midToSlope;
        for (int i = 0; i < pointsSize; i++) {
            int x1 = points[i][0];
            int y1 = points[i][1];
            for (int j = i + 1; j < pointsSize; j++) {
                int x2 = points[j][0];
                int y2 = points[j][1];
                int dx = x1 - x2;
                int dy = y1 - y2;
                float k, b;
                if (x2 == x1) {
                    k = inf;
                    b = x1;
                } else {
                    k = (float)(y2 - y1) / (x2 - x1);
                    b = (float)(y1 * dx - x1 * dy) / dx;
                }

                int middle = (x1 + x2) * 10000 + (y1 + y2);
                slopeToIntercept[k].push_back(b);
                midToSlope[middle].push_back(k);
            }
        }

        for (auto& [_, sti] : slopeToIntercept) {
            int stiSize = sti.size();
            if (stiSize == 1) {
                continue;
            }

            map<float, int> cnt;
            for (float b : sti) {
                cnt[b]++;
            }

            int sum = 0;
            for (auto& [_, count] : cnt) {
                retVal += (sum * count);
                sum += count;
            }
        }

        for (auto& [_, mts] : midToSlope) {
            int mtsSize = mts.size();
            if (mtsSize == 1) {
                continue;
            }

            map<float, int> cnt;
            for (float k : mts) {
                cnt[k]++;
            }

            int sum = 0;
            for (auto& [_, count] : cnt) {
                retVal -= (sum * count);
                sum += count;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{-3, 2}, {3, 0}, {2, 3}, {3, 2}, {2, -3}}}, {{{0, 0}, {1, 0}, {0, 1}, {2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
     *  Output: 2
     *
     *  Input: points = [[0,0],[1,0],[0,1],[2,1]]
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countTrapezoids(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
