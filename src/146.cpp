#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct DoublyLinkedNode {
    int key;
    int value;
    DoublyLinkedNode* prev;
    DoublyLinkedNode* next;
    DoublyLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DoublyLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
   private:
    int capacity;
    unordered_map<int, DoublyLinkedNode*> cache;
    int size;

    DoublyLinkedNode* head;
    DoublyLinkedNode* tail;

   public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;

        head = new DoublyLinkedNode();
        tail = new DoublyLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    ~LRUCache() {
        DoublyLinkedNode* node = head;
        while (node != tail) {
            DoublyLinkedNode* current = node;
            node = node->next;
            delete current;
        }
        delete node;
    }
    void addToHead(DoublyLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(DoublyLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void moveToHead(DoublyLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DoublyLinkedNode* removeTail() {
        DoublyLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
    int get(int key) {
        int retVal = -1;

        if (cache.count(key) == 0) {
            return retVal;
        }

        DoublyLinkedNode* node = cache[key];
        moveToHead(node);
        retVal = node->value;

        return retVal;
    }
    void put(int key, int value) {
        if (cache.count(key) == 0) {
            DoublyLinkedNode* node = new DoublyLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > capacity) {
                DoublyLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        } else {
            DoublyLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{
        {{"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"},
         {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}}},
        {{"LRUCache", "put", "put", "get", "put", "put", "get"}, {{2}, {2, 1}, {2, 2}, {2}, {1, 1}, {4, 1}, {2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
     *  [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
     *  Output
     *  [null, null, null, 1, null, -1, null, -1, 3, 4]
     *
     *  Input
     *  ["LRUCache", "put", "put", "get", "put", "put", "get"]
     *  [[2], [2,1], [2,2], [2], [1,1], [4,1], [2]]
     *  Output
     *  [null, null, null, 2, null, null, -1]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].values[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].values[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        LRUCache cLRUCache(testData[i].values[0][0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ");
            if (testData[i].methods[j].compare("LRUCache") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("get") == 0) {
                int retVal = cLRUCache.get(testData[i].values[j][0]);
                cout << retVal;
            } else if (testData[i].methods[j].compare("put") == 0) {
                cLRUCache.put(testData[i].values[j][0], testData[i].values[j][1]);
                cout << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
