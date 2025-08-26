#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int retVal = 0;

        int maxDiagonal = 0;
        for (const auto& dimension : dimensions) {
            int width = dimension[0];
            int height = dimension[1];
            int diagonal = (width * width + height * height);
            int area = width * height;

            if (diagonal > maxDiagonal) {
                maxDiagonal = diagonal;
                retVal = area;
            } else if (diagonal == maxDiagonal) {
                retVal = max(retVal, area);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> dimensions;
    };
    vector<subject> testData{{{{9, 3}, {8, 6}}}, {{{3, 4}, {4, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dimensions = [[9,3],[8,6]]
     *  Output: 48
     *
     *  Input: dimensions = [[3,4],[4,3]]
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dimensions = [";
        for (long unsigned int j = 0; j < testData[i].dimensions.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].dimensions[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].dimensions[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.areaOfMaxDiagonal(testData[i].dimensions);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
