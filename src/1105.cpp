#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int retVal = 0;

        int booksSize = books.size();

        // dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
        vector<int> dp(booksSize + 1, 0);
        dp[0] = 0;
        dp[1] = books[0][1];
        for (int i = 1; i <= booksSize; ++i) {
            // new shelf built to hold current book
            int remainingShelfWidth = shelfWidth - books[i - 1][0];
            int maxHeight = books[i - 1][1];
            dp[i] = dp[i - 1] + maxHeight;

            // calculate the height when previous books are added onto a new shelf
            int j = i - 1;
            while ((j > 0) && (remainingShelfWidth - books[j - 1][0] >= 0)) {
                remainingShelfWidth -= books[j - 1][0];
                maxHeight = max(maxHeight, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + maxHeight);
                j--;
            }
        }
        retVal = dp[booksSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> books;
        int shelfWidth;
    };
    vector<subject> testData{{{{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}}, 4},
                             {{{1, 3}, {2, 4}, {3, 2}}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelfWidth = 4
     *  Output: 6
     *
     *  Input: books = [[1,3],[2,4],[3,2]], shelfWidth = 6
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: books = [";
        for (long unsigned int j = 0; j < testData[i].books.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].books[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].books[j][k];
            }
            cout << "]";
        }
        cout << "]" << ", shelfWidth = " << testData[i].shelfWidth << "\n";

        answer = cSolution.minHeightShelves(testData[i].books, testData[i].shelfWidth);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
