#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define INF (int)(0x3f3f3f3f)  // 0 <= arr1[i], arr2[i] <= 10^9

   public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int retVal = -1;

        sort(arr2.begin(), arr2.end());

        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        int arr1Size = arr1.size();
        int arr2Size = arr2.size();

        vector<vector<int>> dp(arr1Size + 1, vector<int>(min(arr2Size, arr1Size) + 1, INF));
        dp[0][0] = -1;

        for (int i = 1; i <= arr1Size; i++) {
            for (int j = 0; j <= min(i, arr2Size); j++) {
                if (arr1[i - 1] > dp[i - 1][j]) {
                    dp[i][j] = arr1[i - 1];
                }

                if ((j > 0) && (dp[i - 1][j - 1] != INF)) {
                    auto it = upper_bound(arr2.begin() + j - 1, arr2.end(), dp[i - 1][j - 1]);
                    if (it != arr2.end()) {
                        dp[i][j] = min(dp[i][j], *it);
                    }
                }

                if ((i == arr1Size) && (dp[i][j] != INF)) {
                    retVal = j;
                    return retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr1;
        vector<int> arr2;
    };
    vector<subject> testData{
        {{1, 5, 3, 6, 7}, {1, 3, 2, 4}}, {{1, 5, 3, 6, 7}, {4, 3, 1}}, {{1, 5, 3, 6, 7}, {1, 6, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
     *  Output: 1
     *
     *  Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
     *  Output: 2
     *
     *  Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr1 = [";
        for (long unsigned int j = 0; j < testData[i].arr1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr1[j];
        }
        cout << "], arr2 = [";
        for (long unsigned int j = 0; j < testData[i].arr2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr2[j];
        }
        cout << "]\n";

        answer = cSolution.makeArrayIncreasing(testData[i].arr1, testData[i].arr2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
