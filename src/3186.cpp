#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumTotalDamage(vector<int>& power) {
        long long retVal = 0;

        map<int, int> count;
        for (int p : power) {
            count[p]++;
        }

        vector<pair<int, int>> vec = {{-1e9, 0}};
        for (auto& p : count) {
            vec.push_back(p);
        }
        int n = vec.size();

        vector<long long> f(n, 0);
        long long mx = 0;
        for (int i = 1, j = 1; i < n; i++) {
            while (j < i && vec[j].first < vec[i].first - 2) {
                mx = max(mx, f[j]);
                j++;
            }
            f[i] = mx + 1LL * vec[i].first * vec[i].second;
        }

        for (int i = 1; i < n; i++) {
            retVal = max(retVal, f[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> power;
    };
    vector<subject> testData{{{1, 1, 3, 4}}, {{7, 1, 6, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: power = [1,1,3,4]
     *  Output: 6
     *
     *  Input: power = [7,1,6,6]
     *  Output: 13
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: power = [";
        for (long unsigned int j = 0; j < testData[i].power.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].power[j];
        }
        cout << "]\n";

        answer = cSolution.maximumTotalDamage(testData[i].power);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
