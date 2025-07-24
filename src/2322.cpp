#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> adjacent;
    int sum = 0;
    int ret = 0;

    int calc(int part1, int part2, int part3) {
        int retVal = max(part1, max(part2, part3)) - min(part1, min(part2, part3));

        return retVal;
    }
    int dfs(vector<int> &nums, int x, int f) {
        int retVal = nums[x];

        for (auto &y : adjacent[x]) {
            if (y == f) {
                continue;
            }
            retVal ^= dfs(nums, y, x);
        }

        for (auto &y : adjacent[x]) {
            if (y == f) {
                dfs2(nums, y, x, retVal, x);
            }
        }

        return retVal;
    };
    int dfs2(vector<int> &nums, int x, int f, int oth, int anc) {
        int retVal = nums[x];

        for (auto &y : adjacent[x]) {
            if (y == f) {
                continue;
            }
            retVal ^= dfs2(nums, y, x, oth, anc);
        }
        if (f != anc) {
            ret = min(ret, calc(oth, retVal, sum ^ oth ^ retVal));
        }

        return retVal;
    };

   public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges) {
        int retVal = 0;

        int numsSize = nums.size();

        adjacent.resize(numsSize);
        for (auto &v : edges) {
            adjacent[v[0]].push_back(v[1]);
            adjacent[v[1]].push_back(v[0]);
        }

        sum = 0;
        for (int x : nums) {
            sum ^= x;
        }

        ret = numeric_limits<int>::max();
        dfs(nums, 0, -1);
        retVal = ret;

        adjacent.clear();

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> nums;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{{1, 5, 5, 4, 11}, {{0, 1}, {1, 2}, {1, 3}, {3, 4}}},
                             {{5, 5, 2, 4, 4, 2}, {{0, 1}, {1, 2}, {5, 2}, {4, 3}, {1, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
     *  Output: 9
     *
     *  Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumScore(testData[i].nums, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
