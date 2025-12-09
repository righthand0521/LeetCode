#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int specialTriplets(vector<int>& nums) {
        int retVal = 0;

        int numSize = nums.size();

        unordered_map<int, int> numCnt(numSize * 2);
        for (int v : nums) {
            numCnt[v]++;
        }

        unordered_map<int, int> numPartialCnt(numSize * 2);
        for (int v : nums) {
            int target = v * 2;
            int lCnt = numPartialCnt[target];
            numPartialCnt[v]++;

            int rCnt = numCnt[target] - numPartialCnt[target];
            retVal = (retVal + (lCnt * 1LL * rCnt % MODULO)) % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{6, 3, 6}}, {{0, 1, 0, 0}}, {{8, 4, 2, 8, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [6,3,6]
     *  Output: 1
     *
     *  Input: nums = [0,1,0,0]
     *  Output: 1
     *
     *  Input: nums = [8,4,2,8,4]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.specialTriplets(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
