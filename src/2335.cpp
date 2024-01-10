#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define BRUTE_FORCE (0)
#define MATH_1 (0)
#define MATH_2 (1)
   public:
    int fillCups(vector<int>& amount) {
        int retVal = 0;

#if (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        /* Intuition
         *  142: 131, 021, 010, 000
         *  544: 434, 333, 223, 122, 111, 001, 000
         *  500: 400, 300, 200, 100, 000
         */
        sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
            // descending order
            return (n1 > n2);
        });
        while (amount[0] > 0) {
            if (amount[0] > 0) {
                amount[0] -= 1;
            }

            if (amount[1] > 0) {
                amount[1] -= 1;
            }

            ++retVal;

            sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
                // descending order
                return (n1 > n2);
            });
        }
#elif (MATH_1)
        cout << "MATH_1\n";

        /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
         *  Let amount[2] < amount[1] < amount[0]
         *  1. If amount[2] + amount[1] <= amount[0]
         *     => amount[0] is the minimum number of seconds needed
         *  2. If amount[2] + amount[1] > amount[0]
         *     Let Exceed = amount[2] + amount[1] - amount[0]
         *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
         *     => (Exceed / 2) + amount[0]
         *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
         *        = (amount[2] + amount[1] + amount[0]) / 2
         *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
         *     => ((Exceed - 1) / 2) + amount[0] + 1
         *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
         *        = (amount[2] + amount[1] + amount[0] + 1) / 2
         */
        sort(amount.begin(), amount.end());
        if (amount[0] + amount[1] <= amount[2]) {
            retVal = amount[2];
        } else {
            retVal = (amount[0] + amount[1] + amount[2] + 1) / 2;
        }
#elif (MATH_2)
        cout << "MATH_2\n";

        /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
         *  Let amount[2] < amount[1] < amount[0]
         *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds
         * needed
         */
        int maxAmount = 0;
        for (auto n : amount) {
            maxAmount = max(maxAmount, n);
            retVal += n;
        }
        retVal = (retVal + 1) / 2;
        retVal = max(retVal, maxAmount);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> amount;
    };
    vector<subject> testData{{{1, 4, 2}}, {{5, 4, 4}}, {{5, 0, 0}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: amount = [";
        for (long unsigned int j = 0; j < testData[i].amount.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].amount[j];
        }
        cout << "]\n";

        answer = cSolution.fillCups(testData[i].amount);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
