#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Helper {
   private:
    int x;
    long long result;
    set<pair<int, int>> large, small;
    unordered_map<int, int> occ;

    void internalInsert(const pair<int, int>& p) {
        int largeSize = large.size();
        if ((largeSize < x) || (p > *large.begin())) {
            result += (static_cast<long long>(p.first) * p.second);
            large.insert(p);
            largeSize = large.size();
            if (largeSize > x) {
                result -= (static_cast<long long>(large.begin()->first) * large.begin()->second);
                auto transfer = *large.begin();
                large.erase(transfer);
                small.insert(transfer);
            }
        } else {
            small.insert(p);
        }
    }
    void internalRemove(const pair<int, int>& p) {
        if (p >= *large.begin()) {
            result -= (static_cast<long long>(p.first) * p.second);
            large.erase(p);
            if (!small.empty()) {
                result += (static_cast<long long>(small.rbegin()->first) * small.rbegin()->second);
                auto transfer = *small.rbegin();
                small.erase(transfer);
                large.insert(transfer);
            }
        } else {
            small.erase(p);
        }
    }

   public:
    Helper(int x) {
        this->x = x;
        this->result = 0;
    }
    void insert(int num) {
        if (occ[num]) {
            internalRemove({occ[num], num});
        }
        ++occ[num];
        internalInsert({occ[num], num});
    }
    void remove(int num) {
        internalRemove({occ[num], num});
        --occ[num];
        if (occ[num]) {
            internalInsert({occ[num], num});
        }
    }
    long long get() {
        long long retVal = result;

        return retVal;
    }
};
class Solution {
   public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        vector<long long> retVal;

        Helper helper(x);

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            helper.insert(nums[i]);
            if (i >= k) {
                helper.remove(nums[i - k]);
            }
            if (i >= k - 1) {
                retVal.push_back(helper.get());
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
        int x;
    };
    vector<subject> testData{{{1, 1, 2, 2, 3, 4, 2, 3}, 6, 2}, {{3, 8, 7, 8, 7, 5}, 2, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
     *  Output: [6,10,12]
     *
     *  Input: nums = [3,8,7,8,7,5], k = 2, x = 2
     *  Output: [11,15,15,15,12]
     */

    Solution cSolution;
    vector<long long> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << ", x = " << testData[i].x << "\n";

        answer = cSolution.findXSum(testData[i].nums, testData[i].k, testData[i].x);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
