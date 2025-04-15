#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> c;
    vector<int> a;

    void Update(int pos) {
        int cSize = c.size();
        while (pos < cSize) {
            c[pos] += 1;
            pos += (pos & (-pos));
        }
    }
    int Query(int pos) {
        int retVal = 0;

        while (pos > 0) {
            retVal += c[pos];
            pos -= (pos & (-pos));
        }

        return retVal;
    }
    int getId(int x) {
        int retVal = lower_bound(a.begin(), a.end(), x) - a.begin() + 1;

        return retVal;
    }
    void Init(int length) {
        //
        c.resize(length, 0);
    }
    void Discretization(vector<int>& nums) {
        a.assign(nums.begin(), nums.end());
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

   public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        Discretization(nums);
        Init(numsSize + 5);
        for (int i = numsSize - 1; i >= 0; --i) {
            int id = getId(nums[i]);
            retVal.emplace_back(Query(id - 1));
            Update(id);
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 2, 6, 1}}, {{-1}}, {{-1, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,2,6,1]
     *  Output: [2,1,1,0]
     *
     *  Input: nums = [-1]
     *  Output: [0]
     *
     *  Input: nums = [-1,-1]
     *  Output: [0,0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countSmaller(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
