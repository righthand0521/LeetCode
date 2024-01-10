#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int atMostDifferent(vector<int>& nums, int k) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = nums.size();
        int head = 0;
        int tail = 0;
        while (tail < len) {
            hashTable[nums[tail]]++;
            tail++;

            while ((int)hashTable.size() > k) {
                hashTable[nums[head]]--;
                if (hashTable[nums[head]] == 0) {
                    hashTable.erase(nums[head]);
                }
                head++;
            }
            retVal += (tail - head);
        }

        return retVal;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int retVal = 0;

        // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
        retVal = atMostDifferent(nums, k) - atMostDifferent(nums, k - 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 1, 2, 3}, 2}, {{1, 2, 1, 3, 4}, 3}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.subarraysWithKDistinct(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
