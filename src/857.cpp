#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        double retVal = numeric_limits<double>::max();

        int qualitySize = quality.size();

        vector<pair<double, int>> wageToQualityRatio;
        for (int i = 0; i < qualitySize; i++) {
            wageToQualityRatio.push_back({static_cast<double>(wage[i]) / quality[i], quality[i]});
        }
        sort(wageToQualityRatio.begin(), wageToQualityRatio.end());

        int highestQualityWorkersSize;
        double currentTotalQuality = 0;
        priority_queue<int> highestQualityWorkers;
        for (int i = 0; i < qualitySize; i++) {
            highestQualityWorkers.push(wageToQualityRatio[i].second);
            currentTotalQuality += wageToQualityRatio[i].second;

            highestQualityWorkersSize = highestQualityWorkers.size();
            if (highestQualityWorkersSize > k) {
                currentTotalQuality -= highestQualityWorkers.top();
                highestQualityWorkers.pop();
            }

            highestQualityWorkersSize = highestQualityWorkers.size();
            if (highestQualityWorkersSize == k) {
                retVal = min(retVal, currentTotalQuality * wageToQualityRatio[i].first);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> quality;
        vector<int> wage;
        int k;
    };
    vector<subject> testData{{{10, 20, 5}, {70, 50, 30}, 2}, {{3, 1, 10, 10, 1}, {4, 8, 2, 2, 7}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: quality = [10,20,5], wage = [70,50,30], k = 2
     *  Output: 105.00000
     *
     *  Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
     *  Output: 30.66667
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: quality = [";
        for (long unsigned int j = 0; j < testData[i].quality.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].quality[j];
        }
        cout << "], wage = [";
        for (long unsigned int j = 0; j < testData[i].wage.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].wage[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.mincostToHireWorkers(testData[i].quality, testData[i].wage, testData[i].k);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
