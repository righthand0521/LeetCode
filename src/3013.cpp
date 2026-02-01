#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Container {
   private:
    int k;
    multiset<int> st1;
    multiset<int> st2;
    long long sm;

   public:
    Container(int k) : k(k), sm(0) {
        //
    }

    void adjust() {
        while (1) {
            int st1Size = st1.size();
            int st2Size = st2.size();
            if (st1Size >= k) {
                break;
            } else if (st2Size <= 0) {
                break;
            }
            int x = *(st2.begin());
            st1.emplace(x);
            sm += x;
            st2.erase(st2.begin());
        }

        while (1) {
            int st1Size = st1.size();
            if (st1Size <= k) {
                break;
            }
            int x = *prev(st1.end());
            st2.emplace(x);
            st1.erase(prev(st1.end()));
            sm -= x;
        }
    }
    void add(int x) {
        if ((st2.empty() == false) && (x >= *(st2.begin()))) {
            st2.emplace(x);
        } else {
            st1.emplace(x);
            sm += x;
        }

        adjust();
    }
    void erase(int x) {
        auto it = st1.find(x);
        if (it != st1.end()) {
            st1.erase(it), sm -= x;
        } else {
            st2.erase(st2.find(x));
        }

        adjust();
    }
    long long sum() {
        long long retVal = sm;

        return retVal;
    }
};
class Solution {
   public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        long long retVal = 0;

        int numsSize = nums.size();

        Container cnt(k - 2);
        for (int i = 1; i < k - 1; i++) {
            cnt.add(nums[i]);
        }

        retVal = cnt.sum() + nums[k - 1];
        for (int i = k; i < numsSize; i++) {
            int j = i - dist - 1;
            if (j > 0) {
                cnt.erase(nums[j]);
            }
            cnt.add(nums[i - 1]);
            retVal = min(retVal, cnt.sum() + nums[i]);
        }
        retVal += nums[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
        int dist;
    };
    vector<subject> testData{{{1, 3, 2, 6, 4, 2}, 3, 3}, {{10, 1, 2, 2, 2, 1}, 4, 3}, {{10, 8, 18, 9}, 3, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
     *  Output: 5
     *
     *  Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
     *  Output: 15
     *
     *  Input: nums = [10,8,18,9], k = 3, dist = 1
     *  Output: 36
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << ", dist = " << testData[i].dist << "\n";

        answer = cSolution.minimumCost(testData[i].nums, testData[i].k, testData[i].dist);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
