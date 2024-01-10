#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> retVal;

        int sum = 0;
        int carry = 0;
        int idx = num.size() - 1;
        while ((idx >= 0) && (k > 0)) {
            sum = num[idx] + k % 10 + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            k /= 10;
            --idx;
        }
        while (idx >= 0) {
            sum = num[idx] + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            --idx;
        }
        while (k > 0) {
            sum = k % 10 + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            k /= 10;
        }
        if (sum >= 10) {
            carry = sum / 10;
            retVal.push_back(carry);
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> num;
        int k;
    };
    vector<subject> testData{{{1, 2, 0, 0}, 34}, {{2, 7, 4}, 181}, {{2, 1, 5}, 806}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: num = [1,2,0,0], k = 34
     *  Output: [1,2,3,4]
     *
     *  Input: num = [2,7,4], k = 181
     *  Output: [4,5,5]
     *
     *  Input: num = [2,1,5], k = 806
     *  Output: [1,0,2,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].num[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.addToArrayForm(testData[i].num, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
