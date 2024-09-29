#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

class Node {
   private:
    Node* head;                        // Dummy head
    Node* tail;                        // Dummy tail
    unordered_map<string, Node*> map;  // Mapping from key to its node

   public:
    int freq;
    Node* prev;
    Node* next;
    unordered_set<string> keys;

    Node(int freq) : freq(freq), prev(nullptr), next(nullptr) {}
};
class AllOne {
   private:
    Node* head;                        // Dummy head
    Node* tail;                        // Dummy tail
    unordered_map<string, Node*> map;  // Mapping from key to its node

    void removeNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;

        prevNode->next = nextNode;  // Link previous node to next node
        nextNode->prev = prevNode;  // Link next node to previous node

        delete node;  // Free the memory of the removed node
    }

   public:
    AllOne() {
        head = new Node(0);  // Create dummy head
        tail = new Node(0);  // Create dummy tail
        head->next = tail;   // Link dummy head to dummy tail
        tail->prev = head;   // Link dummy tail to dummy head
    }
    ~AllOne() {
        while (head != tail) {
            Node* pRemove = head;
            head = head->next;
            delete pRemove;
        }
        delete head;
    }
    void inc(string key) {
        if (map.find(key) != map.end()) {
            Node* node = map[key];
            int freq = node->freq;
            node->keys.erase(key);  // Remove key from current node

            Node* nextNode = node->next;
            if ((nextNode == tail) || (nextNode->freq != freq + 1)) {
                // Create a new node if next node does not exist or freq is not freq + 1
                Node* newNode = new Node(freq + 1);
                newNode->keys.insert(key);
                newNode->prev = node;
                newNode->next = nextNode;
                node->next = newNode;
                nextNode->prev = newNode;
                map[key] = newNode;
            } else {
                // Increment the existing next node
                nextNode->keys.insert(key);
                map[key] = nextNode;
            }

            // Remove the current node if it has no keys left
            if (node->keys.empty()) {
                removeNode(node);
            }
        } else {  // Key does not exist
            Node* firstNode = head->next;
            if ((firstNode == tail) || (firstNode->freq > 1)) {
                // Create a new node
                Node* newNode = new Node(1);
                newNode->keys.insert(key);
                newNode->prev = head;
                newNode->next = firstNode;
                head->next = newNode;
                firstNode->prev = newNode;
                map[key] = newNode;
            } else {
                firstNode->keys.insert(key);
                map[key] = firstNode;
            }
        }
    }
    void dec(string key) {
        if (map.find(key) == map.end()) {
            return;  // Key does not exist
        }

        Node* node = map[key];
        node->keys.erase(key);
        int freq = node->freq;

        if (freq == 1) {
            // Remove the key from the map if freq is 1
            map.erase(key);
        } else {
            Node* prevNode = node->prev;
            if ((prevNode == head) || (prevNode->freq != freq - 1)) {
                // Create a new node if the previous node does not exist or freq is not freq - 1
                Node* newNode = new Node(freq - 1);
                newNode->keys.insert(key);
                newNode->prev = prevNode;
                newNode->next = node;
                prevNode->next = newNode;
                node->prev = newNode;
                map[key] = newNode;
            } else {
                // Decrement the existing previous node
                prevNode->keys.insert(key);
                map[key] = prevNode;
            }
        }

        // Remove the node if it has no keys left
        if (node->keys.empty()) {
            removeNode(node);
        }
    }
    string getMaxKey() {
        string retVal = "";

        if (tail->prev != head) {
            retVal = *(tail->prev->keys.begin());  // Return one of the keys from the tail's previous node
        }

        return retVal;
    }
    string getMinKey() {
        string retVal = "";

        if (head->next != tail) {
            retVal = *(head->next->keys.begin());  // Return one of the keys from the head's next node
        }

        return retVal;
    }
};
/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<string>> values;
    };
    vector<subject> testData{{{"AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"},
                              {{}, {"hello"}, {"hello"}, {}, {}, {"leet"}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
     *  [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
     *  Output
     *  [null, null, null, "hello", "hello", null, "hello", "leet"]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].values[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << testData[i].values[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        AllOne cAllOne;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("AllOne") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("inc") == 0) {
                cAllOne.inc(testData[i].values[j][0]);
                cout << "null";
            } else if (testData[i].methods[j].compare("dec") == 0) {
                cAllOne.dec(testData[i].values[j][0]);
                cout << "null";
            } else if (testData[i].methods[j].compare("getMaxKey") == 0) {
                string retVal = cAllOne.getMaxKey();
                cout << "\"" << retVal << "\"";
            } else if (testData[i].methods[j].compare("getMinKey") == 0) {
                string retVal = cAllOne.getMinKey();
                cout << "\"" << retVal << "\"";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
