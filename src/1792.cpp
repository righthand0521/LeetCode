#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    double calculateGain(int passes, int totalStudents) {
        double retVal = 0;

        retVal = (double)(passes + 1) / (totalStudents + 1) - (double)passes / totalStudents;

        return retVal;
    };

   public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        double retVal = 0;

        // Max heap to store (-gain, passes, totalStudents)
        priority_queue<pair<double, pair<int, int>>> maxHeap;
        for (const auto& singleClass : classes) {
            maxHeap.push({calculateGain(singleClass[0], singleClass[1]), {singleClass[0], singleClass[1]}});
        }

        // Distribute extra students
        while (extraStudents--) {
            auto [currentGain, classInfo] = maxHeap.top();
            maxHeap.pop();
            int passes = classInfo.first;
            int totalStudents = classInfo.second;
            maxHeap.push({calculateGain(passes + 1, totalStudents + 1), {passes + 1, totalStudents + 1}});
        }

        // Calculate the final average pass ratio
        double totalPassRatio = 0;
        while (maxHeap.empty() == false) {
            auto [_, classInfo] = maxHeap.top();
            maxHeap.pop();
            totalPassRatio += (double)classInfo.first / classInfo.second;
        }
        int classesSize = classes.size();
        retVal = totalPassRatio / classesSize;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> classes;
        int extraStudents;
    };
    vector<subject> testData{{{{1, 2}, {3, 5}, {2, 2}}, 2}, {{{2, 4}, {3, 9}, {4, 5}, {2, 10}}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
     *  Output: 0.78333
     *
     *  Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
     *  Output: 0.53485
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: classes = [";
        for (long unsigned int j = 0; j < testData[i].classes.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].classes[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].classes[j][k];
            }
            cout << "]";
        }
        cout << "], extraStudents = " << testData[i].extraStudents << "\n";

        answer = cSolution.maxAverageRatio(testData[i].classes, testData[i].extraStudents);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
