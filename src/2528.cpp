#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    bool check(int r, int k, long long val, vector<long long>& cnt, int stationsSize) {
        bool retVal = true;

        vector<long long> diff = cnt;
        long long sum = 0;
        long long remaining = k;
        for (int i = 0; i < stationsSize; i++) {
            sum += diff[i];
            if (sum >= val) {
                continue;
            }

            long long add = val - sum;
            if (remaining < add) {
                retVal = false;
                break;
            }

            remaining -= add;
            int end = min(stationsSize, i + 2 * r + 1);
            diff[end] -= add;
            sum += add;
        }

        return retVal;
    };

   public:
    long long maxPower(vector<int>& stations, int r, int k) {
        long long retVal = 0;

        int stationsSize = stations.size();

        vector<long long> cnt(stationsSize + 1);
        for (int i = 0; i < stationsSize; i++) {
            int left = max(0, i - r);
            int right = min(stationsSize, i + r + 1);
            cnt[left] += stations[i];
            cnt[right] -= stations[i];
        }

        long long low = *min_element(cnt.begin(), cnt.end());
        long long high = accumulate(stations.begin(), stations.end(), 0LL) + k;
        while (low <= high) {
            long long middle = low + (high - low) / 2;
            if (check(r, k, middle, cnt, stationsSize) == true) {
                retVal = middle;
                low = middle + 1;
            } else {
                high = middle - 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> stations;
        int r;
        int k;
    };
    vector<subject> testData{{{1, 2, 4, 5, 0}, 1, 2}, {{4, 4, 4, 4}, 0, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: stations = [1,2,4,5,0], r = 1, k = 2
     *  Output: 5
     *
     *  Input: stations = [4,4,4,4], r = 0, k = 3
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: stations = [";
        for (long unsigned int j = 0; j < testData[i].stations.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].stations[j];
        }
        cout << "], r = " << testData[i].r << ", k = " << testData[i].k << "\n";

        answer = cSolution.maxPower(testData[i].stations, testData[i].r, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
