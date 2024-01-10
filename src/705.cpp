#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MyHashSet {
   public:
    vector<vector<int>> bucket;
    int mod;

    MyHashSet() {
        mod = 1000;
        bucket = vector<vector<int>>(mod);
    }
    void add(int key) {
        int idx = key % mod;
        if (count(bucket[idx].begin(), bucket[idx].end(), key) == 0) {
            bucket[idx].emplace_back(key);
        }
    }
    void remove(int key) {
        int idx = key % mod;
        for (auto iterator = bucket[idx].begin(); iterator != bucket[idx].end(); ++iterator) {
            if (*iterator == key) {
                bucket[idx].erase(iterator);
                break;
            }
        }
    }
    bool contains(int key) {
        bool retVal = false;

        int idx = key % mod;
        if (count(bucket[idx].begin(), bucket[idx].end(), key) != 0) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{
        {{"MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"},
         {{}, {1}, {2}, {1}, {3}, {2}, {2}, {2}, {2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
     *  [[], [1], [2], [1], [3], [2], [2], [2], [2]]
     *  Output
     *  [null, null, null, true, false, null, true, null, false]
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

        MyHashSet cMyHashSet;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MyHashSet") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("add") == 0) {
                cMyHashSet.add(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("remove") == 0) {
                cMyHashSet.remove(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("contains") == 0) {
                bool retVal = cMyHashSet.contains(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
