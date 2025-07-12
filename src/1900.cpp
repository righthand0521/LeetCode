#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   private:
    static const int dpSize = 30;  // 2 <= n <= 28, 1 <= firstPlayer < secondPlayer <= n.
    int F[dpSize][dpSize][dpSize];
    int G[dpSize][dpSize][dpSize];

   public:
    pair<int, int> dp(int n, int f, int s) {
        pair<int, int> retVal;

        if (F[n][f][s]) {
            retVal = {F[n][f][s], G[n][f][s]};
            return retVal;
        }

        if (f + s == n + 1) {
            retVal = {1, 1};
            return retVal;
        }

        // F(n,f,s)=F(n,n+1-s,n+1-f)
        if (f + s > n + 1) {
            tie(F[n][f][s], G[n][f][s]) = dp(n, n + 1 - s, n + 1 - f);
            retVal = {F[n][f][s], G[n][f][s]};
            return retVal;
        }

        int earliest = numeric_limits<int>::max();
        int latest = numeric_limits<int>::min();
        int nHalf = (n + 1) / 2;

        // On the left or in the middle
        if (s <= nHalf) {
            for (int i = 0; i < f; ++i) {
                for (int j = 0; j < s - f; ++j) {
                    auto [x, y] = dp(nHalf, i + 1, i + j + 2);
                    earliest = min(earliest, x);
                    latest = max(latest, y);
                }
            }
        } else {  // s on the right
            int sPrime = n + 1 - s;
            int middle = (n - 2 * sPrime + 1) / 2;
            for (int i = 0; i < f; ++i) {
                for (int j = 0; j < sPrime - f; ++j) {
                    auto [x, y] = dp(nHalf, i + 1, i + j + middle + 2);
                    earliest = min(earliest, x);
                    latest = max(latest, y);
                }
            }
        }

        retVal = {F[n][f][s] = earliest + 1, G[n][f][s] = latest + 1};

        return retVal;
    }

    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        vector<int> retVal;

        // F(n,f,s) = F(n,s,f)
        if (firstPlayer > secondPlayer) {
            swap(firstPlayer, secondPlayer);
        }

        memset(F, 0, sizeof(F));
        memset(G, 0, sizeof(G));
        auto [earliest, latest] = dp(n, firstPlayer, secondPlayer);
        retVal = {earliest, latest};

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int firstPlayer;
        int secondPlayer;
    };
    vector<subject> testData{{11, 2, 4}, {5, 1, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 11, firstPlayer = 2, secondPlayer = 4
     *  Output: [3,4]
     *
     *  Input: n = 5, firstPlayer = 1, secondPlayer = 5
     *  Output: [1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", firstPlayer = " << testData[i].firstPlayer
             << ", secondPlayer = " << testData[i].secondPlayer << "\n";

        answer = cSolution.earliestAndLatest(testData[i].n, testData[i].firstPlayer, testData[i].secondPlayer);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
