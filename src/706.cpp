#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MyHashMap {
   public:
    vector<vector<pair<int, int>>> map;
    int mod;

    MyHashMap() {
        mod = 1000;
        map = vector<vector<pair<int, int>>>(mod);
    }
    void put(int key, int value) {
        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                (*iterator).second = value;
                return;
            }
        }
        map[idx].push_back(make_pair(key, value));
    }
    int get(int key) {
        int retVal = -1;

        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                retVal = (*iterator).second;
            }
        }

        return retVal;
    }
    void remove(int key) {
        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                map[idx].erase(iterator);
                break;
            }
        }
    }
};
/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{{{"MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"},
                              {{}, {1, 1}, {2, 2}, {1}, {3}, {2, 1}, {2}, {2}, {2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
     *  [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
     *  Output
     *  [null, null, null, 1, -1, null, 1, null, -1]
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

        MyHashMap cMyHashMap;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MyHashMap") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("put") == 0) {
                cMyHashMap.put(testData[i].val[j][0], testData[i].val[j][1]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("get") == 0) {
                int retVal = cMyHashMap.get(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("remove") == 0) {
                cMyHashMap.remove(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
