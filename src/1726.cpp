#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int tupleSameProduct(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        unordered_map<int, int> pairProductsFrequency;
        for (int firstIndex = 0; firstIndex < numsSize; firstIndex++) {
            for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex++) {
                pairProductsFrequency[nums[firstIndex] * nums[secondIndex]]++;
            }
        }

        for (auto [productValue, productFrequency] : pairProductsFrequency) {
            int pairsOfEqualProduct = (productFrequency - 1) * productFrequency / 2;
            retVal += 8 * pairsOfEqualProduct;  // each pair can form 8 tuples
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 4, 6}}, {{1, 2, 4, 5, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,4,6]
     *  Output: 8
     *
     *  Input: nums = [1,2,4,5,10]
     *  Output: 16
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.tupleSameProduct(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
