#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> retVal;

        for (auto querie : queries) {
            int count = 0;

            int originX = querie[0];
            int originY = querie[1];
            int radius = querie[2];
            for (auto point : points) {
                int x = point[0];
                int y = point[1];

                if (pow(abs(originX - x), 2) + pow(abs(originY - y), 2) <= pow(radius, 2)) {
                    ++count;
                }
            }

            retVal.emplace_back(count);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{{1, 3}, {3, 3}, {5, 3}, {2, 2}}, {{2, 3, 1}, {4, 3, 1}, {1, 1, 2}}},
                             {{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, {{1, 2, 2}, {2, 2, 2}, {4, 3, 2}, {4, 3, 3}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countPoints(testData[i].points, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
