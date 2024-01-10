#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
   private:
    vector<int> nums;
    unordered_map<int, int> indices;

   public:
    RandomizedSet() {
        //
        srand((unsigned)time(NULL));
    }
    bool insert(int val) {
        bool retVal = false;

        if (indices.count(val) != 0) {
            return retVal;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        retVal = true;

        return retVal;
    }
    bool remove(int val) {
        bool retVal = false;

        if (indices.count(val) == 0) {
            return retVal;
        }
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        indices[last] = index;
        nums.pop_back();
        indices.erase(val);
        retVal = true;

        return retVal;
    }
    int getRandom() {
        int retVal = 0;

        int randomIndex = rand() % nums.size();
        retVal = nums[randomIndex];

        return retVal;
    }
};
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{
        {{"RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"},
         {{}, {1}, {2}, {2}, {}, {1}, {2}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
     *  [[], [1], [2], [2], [], [1], [2], []]
     *  Output
     *  [null, true, false, true, 2, true, false, 2]
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

        RandomizedSet cMyHashSet;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("RandomizedSet") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("insert") == 0) {
                bool retVal = cMyHashSet.insert(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("remove") == 0) {
                bool retVal = cMyHashSet.remove(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("getRandom") == 0) {
                int retVal = cMyHashSet.getRandom();
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
