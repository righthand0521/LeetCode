#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    double average(vector<int>& salary) {
        double retVal = 0;

        int salarySize = salary.size();
        double sum = 0;
#if (1)
        sum = accumulate(salary.begin(), salary.end(), 0.);
        sum = sum - *max_element(salary.begin(), salary.end()) - *min_element(salary.begin(), salary.end());
#else
        sort(salary.begin(), salary.end());
        for (int i = 1; i < (salarySize - 1); ++i) {
            sum += salary[i];
        }
#endif
        retVal = sum / (salarySize - 2);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> salary;
    };
    vector<subject> testData{{{4000, 3000, 1000, 2000}}, {{1000, 2000, 3000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: salary = [4000,3000,1000,2000]
     *  Output: 2500.00000
     *
     *  Input: salary = [1000,2000,3000]
     *  Output: 2000.00000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: salary = [";
        for (long unsigned int j = 0; j < testData[i].salary.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].salary[j];
        }
        cout << "]\n";

        answer = cSolution.average(testData[i].salary);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
