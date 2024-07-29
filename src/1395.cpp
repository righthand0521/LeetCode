#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numTeams(vector<int>& rating) {
        int retVal = 0;

        int ratingSize = rating.size();
        for (int middle = 0; middle < ratingSize; ++middle) {
            // Count soldiers with smaller ratings on the left side of the current soldier
            int leftSmaller = 0;
            for (int left = middle - 1; left >= 0; --left) {
                if (rating[left] < rating[middle]) {
                    leftSmaller += 1;
                }
            }

            // Count soldiers with larger ratings on the right side of the current soldier
            int rightLarger = 0;
            for (int right = middle + 1; right < ratingSize; ++right) {
                if (rating[right] > rating[middle]) {
                    rightLarger += 1;
                }
            }

            // Calculate and add the number of ascending rating teams (small-middle-large)
            retVal += (leftSmaller * rightLarger);

            // Calculate soldiers with larger ratings on the left and smaller ratings on the right
            int leftLarger = middle - leftSmaller;
            int rightSmaller = ratingSize - middle - 1 - rightLarger;

            // Calculate and add the number of descending rating teams (large-middle-small)
            retVal += (leftLarger * rightSmaller);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> rating;
    };
    vector<subject> testData{{{2, 5, 3, 4, 1}}, {{2, 1, 3}}, {{1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rating = [2,5,3,4,1]
     *  Output: 3
     *
     *  Input: rating = [2,1,3]
     *  Output: 0
     *
     *  Input: rating = [1,2,3,4]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rating = [";
        for (long unsigned int j = 0; j < testData[i].rating.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].rating[j];
        }
        cout << "]\n";

        answer = cSolution.numTeams(testData[i].rating);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
