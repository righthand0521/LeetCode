#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class LFUCache {
    // (frequency, list of original key-value pairs that have the same frequency)
    unordered_map<int, list<pair<int, int>>> frequencyTable;
    // (key, pair of frequency and the iterator corresponding key int the frequencies map's list)
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> keyTable;
    int cacheSize;
    int leastFrequently;

    void insert(int key, int frequency, int value) {
        frequencyTable[frequency].push_back({key, value});
        keyTable[key] = {frequency, --frequencyTable[frequency].end()};
    }

   public:
    LFUCache(int capacity) {
        cacheSize = capacity;
        leastFrequently = 0;
    }
    int get(int key) {
        int retVal = -1;

        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            return retVal;
        }

        int frequency = it->second.first;
        auto iter = it->second.second;
        pair<int, int> keyValue = *iter;
        frequencyTable[frequency].erase(iter);
        if ((frequencyTable[frequency].empty()) && (leastFrequently == frequency)) {
            ++leastFrequently;
        }
        insert(key, frequency + 1, keyValue.second);
        retVal = keyValue.second;

        return retVal;
    }
    void put(int key, int value) {
        if (cacheSize <= 0) {
            return;
        }

        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            it->second.second->second = value;
            get(key);
            return;
        }

        if (cacheSize == (int)keyTable.size()) {
            keyTable.erase(frequencyTable[leastFrequently].front().first);
            frequencyTable[leastFrequently].pop_front();
        }
        leastFrequently = 1;
        insert(key, 1, value);
    }
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(cacheSize);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(int argc, char** argv) {
#define DISPLAY_NULL (-1)
    struct subject {
        vector<string> methods;
        vector<vector<int>> value;
    };
    vector<subject> testData{{{"LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"},
                              {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {3}, {4, 4}, {1}, {3}, {4}}}};
    int numberOfTestCase = testData.size();

    // LFUCache cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "\"" << testData[i].methods[j] << "\"";
        }
        cout << "]\n[";
        for (long unsigned int j = 0; j < testData[i].value.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].value[j].size(); ++k) {
                cout << ((k == 0) ? "" : ", ") << testData[i].value[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        LFUCache cSolution(testData[i].value[0][0]);
        cout << "Output\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("LFUCache") == 0) {
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("get") == 0) {
                int retVal = cSolution.get(testData[i].value[j][0]);
                cout << ((j == 0) ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("put") == 0) {
                cSolution.put(testData[i].value[j][0], testData[i].value[j][1]);
                cout << ((j == 0) ? "" : ", ") << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
