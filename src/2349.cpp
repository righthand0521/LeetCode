#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class NumberContainers {
   private:
    unordered_map<int, set<int>> numberToIndices;  // Map from number to set of indices
    unordered_map<int, int> indexToNumbers;        // Map from index to number

   public:
    // Constructor: The data structures are already initialized as part of the member variable declarations.
    NumberContainers() {}
    void change(int index, int number) {
        if (indexToNumbers.find(index) != indexToNumbers.end()) {
            int previousNumber = indexToNumbers[index];
            numberToIndices[previousNumber].erase(index);
            if (numberToIndices[previousNumber].empty()) {
                numberToIndices.erase(previousNumber);
            }
        }
        indexToNumbers[index] = number;
        numberToIndices[number].insert(index);
    }
    int find(int number) {
        int retVal = -1;

        if (numberToIndices.find(number) != numberToIndices.end()) {
            // Get the smallest index
            retVal = *numberToIndices[number].begin();
        }

        return retVal;
    }
};
/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{
        {{"NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"},
         {{}, {10}, {2, 10}, {1, 10}, {3, 10}, {5, 10}, {10}, {1, 20}, {10}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
     *  [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
     *  Output
     *  [null, -1, null, null, null, null, 1, null, 2]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].val.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].val[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].val[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        NumberContainers cNumberContainers;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("NumberContainers") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("change") == 0) {
                cNumberContainers.change(testData[i].val[j][0], testData[i].val[j][1]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("find") == 0) {
                int retVal = cNumberContainers.find(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
