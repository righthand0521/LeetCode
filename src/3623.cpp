#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int countTrapezoids(vector<vector<int>>& points) {
        int retVal = 0;

        unordered_map<int, int> pointNum;
        for (auto& point : points) {
            pointNum[point[1]]++;
        }

        long long ans = 0;
        long long totalSum = 0;
        for (auto& [_, point] : pointNum) {
            long long edge = (long long)point * (point - 1) / 2;
            ans += (edge * totalSum);
            ans %= MODULO;
            totalSum += edge;
            totalSum %= MODULO;
        }
        retVal = ans % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}}}, {{{0, 0}, {1, 0}, {0, 1}, {2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
     *  Output: 3
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
