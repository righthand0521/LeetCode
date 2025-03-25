#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool checkCuts(vector<vector<int>>& rectangles, int dim) {
        bool retVal = false;

        // Sort rectangles by their starting coordinate in the given dimension
        sort(rectangles.begin(), rectangles.end(), [dim](const vector<int>& a, const vector<int>& b) {
            //
            return a[dim] < b[dim];
        });

        // Track the furthest ending coordinate seen so far
        int furthestEnd = rectangles[0][dim + 2];
        int gapCount = 0;
        for (size_t i = 1; i < rectangles.size(); i++) {
            vector<int>& rect = rectangles[i];
            // If current rectangle starts after the furthest end we've seen, we found a gap where a cut can be made
            if (furthestEnd <= rect[dim]) {
                gapCount++;
            }
            // Update the furthest ending coordinate
            furthestEnd = max(furthestEnd, rect[dim + 2]);
        }

        // We need at least 2 gaps to create 3 sections
        retVal = (gapCount >= 2);

        return retVal;
    }

   public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        bool retVal = false;

        // Try both horizontal and vertical cuts
        retVal = checkCuts(rectangles, 0) || checkCuts(rectangles, 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> rectangles;
    };
    vector<subject> testData{{5, {{1, 0, 5, 2}, {0, 2, 2, 4}, {3, 2, 5, 3}, {0, 4, 4, 5}}},
                             {4, {{0, 0, 1, 1}, {2, 0, 3, 4}, {0, 2, 2, 3}, {3, 0, 4, 3}}},
                             {4, {{0, 2, 2, 4}, {1, 0, 3, 2}, {2, 2, 3, 4}, {3, 0, 4, 2}, {3, 2, 4, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
     *  Output: true
     *
     *  Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
     *  Output: true
     *
     *  Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", rectangles = [";
        for (long unsigned int j = 0; j < testData[i].rectangles.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].rectangles[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].rectangles[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.checkValidCuts(testData[i].n, testData[i].rectangles);
        cout << "Output: " << (answer ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
