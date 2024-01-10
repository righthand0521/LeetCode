#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

using namespace std;

class SmallestInfiniteSet {
   public:
    int current;
    set<int> record;

    SmallestInfiniteSet() {
        //
        current = 1;
    }
    int popSmallest() {
        int retVal = 0;

        if (record.size()) {
            retVal = *record.begin();
            record.erase(retVal);
        } else {
            ++current;
            retVal = current - 1;
        }

        return retVal;
    }
    void addBack(int num) {
        if (current > num) {
            record.insert(num);
        }
    }
};
/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */

int main(int argc, char **argv) {
    struct subject {
        // unordered_map<string, int> calls;

        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{
        {{"SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest",
          "popSmallest", "popSmallest"},
         {std::numeric_limits<int>::min(), 2, std::numeric_limits<int>::min(), std::numeric_limits<int>::min(),
          std::numeric_limits<int>::min(), 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::min(),
          std::numeric_limits<int>::min()}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest",
     * "popSmallest", "popSmallest"]
     *  [[], [2], [], [], [], [1], [], [], []]
     *  Output
     *  [null, null, 1, 2, 3, null, 1, 4, 5]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        SmallestInfiniteSet cSmallestInfiniteSet;

        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].num[j] != std::numeric_limits<int>::min()) {
                cout << testData[i].num[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("SmallestInfiniteSet") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            }
            if (testData[i].methods[j].compare("addBack") == 0) {
                cSmallestInfiniteSet.addBack(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            }
            if (testData[i].methods[j].compare("popSmallest") == 0) {
                int retVal = cSmallestInfiniteSet.popSmallest();
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
