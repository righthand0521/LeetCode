#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int retVal = 0;

        // Calculate initial number of unrealized customers in first 'minutes' window
        int unrealizedCustomers = 0;
        for (int i = 0; i < minutes; ++i) {
            unrealizedCustomers += customers[i] * grumpy[i];
        }
        int maxUnrealizedCustomers = unrealizedCustomers;

        // Slide the 'minutes' window across the rest of the customers array
        int customersSize = customers.size();
        for (int i = minutes; i < customersSize; ++i) {
            // Add current minute's unsatisfied customers if the owner is grumpy
            // and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i];
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

            // Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers);
        }

        // Start with maximum possible satisfied customers due to secret technique
        int totalCustomers = maxUnrealizedCustomers;

        // Add the satisfied customers during non-grumpy minutes
        for (int i = 0; i < customersSize; ++i) {
            totalCustomers += customers[i] * (1 - grumpy[i]);
        }

        // Return the maximum number of satisfied customers
        retVal = totalCustomers;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> customers;
        vector<int> grumpy;
        int minutes;
    };
    vector<subject> testData{{{1, 0, 1, 2, 1, 1, 7, 5}, {0, 1, 0, 1, 0, 1, 0, 1}, 3}, {{1}, {0}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
     *  Output: 16
     *
     *  Input: customers = [1], grumpy = [0], minutes = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: customers = [";
        for (long unsigned int j = 0; j < testData[i].customers.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].customers[j];
        }
        cout << "], grumpy = [";
        for (long unsigned int j = 0; j < testData[i].grumpy.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].grumpy[j];
        }
        cout << "], minutes = " << testData[i].minutes << "\n";

        answer = cSolution.maxSatisfied(testData[i].customers, testData[i].grumpy, testData[i].minutes);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
