#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int candy(vector<int>& ratings) {
        int retVal = 0;

        int ratingsSize = ratings.size();

        vector<int> left(ratingsSize, 0);
        for (int i = 0; i < ratingsSize; i++) {
            if ((i > 0) && (ratings[i] > ratings[i - 1])) {
                left[i] = left[i - 1] + 1;
            } else {
                left[i] = 1;
            }
        }

        int right = 0;
        for (int i = ratingsSize - 1; i >= 0; i--) {
            if ((i < ratingsSize - 1) && (ratings[i] > ratings[i + 1])) {
                right++;
            } else {
                right = 1;
            }

            retVal += max(left[i], right);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> ratings;
    };
    vector<subject> testData{{{1, 0, 2}}, {{1, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: ratings = [1,0,2]
     *  Output: 5
     *
     *  Input: ratings = [1,2,2]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: ratings = [";
        for (long unsigned int j = 0; j < testData[i].ratings.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].ratings[j];
        }
        cout << "]\n";

        answer = cSolution.candy(testData[i].ratings);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
