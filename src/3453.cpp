#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool check(vector<vector<int>>& squares, double totalArea, double limitY) {
        bool retVal = false;

        double area = 0;
        for (auto& sq : squares) {
            int y = sq[1];
            int l = sq[2];
            if (y < limitY) {
                area += (l * min(limitY - y, (double)l));
            }
        }
        retVal = area >= totalArea / 2;

        return retVal;
    };

   public:
    double separateSquares(vector<vector<int>>& squares) {
        double retVal = 0;

        double maxY = 0;
        double totalArea = 0;
        for (auto& sq : squares) {
            double y = sq[1];
            double l = sq[2];
            totalArea += (l * l);
            maxY = max(maxY, y + l);
        }

        double left = 0;
        double right = maxY;
        double eps = 1e-5;
        while (abs(right - left) > eps) {
            double middle = (right + left) / 2;
            if (check(squares, totalArea, middle) == true) {
                right = middle;
            } else {
                left = middle;
            }
        }
        retVal = right;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> squares;
    };
    vector<subject> testData{{{{0, 0, 1}, {2, 2, 1}}}, {{{0, 0, 2}, {1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: squares = [[0,0,1],[2,2,1]]
     *  Output: 1.00000
     *
     *  Input: squares = [[0,0,2],[1,1,1]]
     *  Output: 1.16667
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: squares = [";
        for (long unsigned int j = 0; j < testData[i].squares.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].squares[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].squares[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.separateSquares(testData[i].squares);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
