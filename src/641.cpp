#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int val, Node* next = NULL, Node* prev = NULL) : val(val), next(next), prev(prev) {}
};
class MyCircularDeque {
   private:
    int capacity;
    Node* head;
    Node* rear;
    int size;

   public:
    MyCircularDeque(int k) {
        capacity = k;
        head = nullptr;
        rear = nullptr;
        size = 0;
    }
    ~MyCircularDeque() {
        while (head != rear) {
            Node* pCurrent = head;
            head = head->next;
            delete pCurrent;
        }
        delete head;
    }
    bool insertFront(int value) {
        bool retVal = false;

        if (isFull() == true) {
            return retVal;
        }

        if (head == NULL) {
            head = new Node(value);
            rear = head;
        } else {
            Node* newHead = new Node(value);
            newHead->next = head;
            head->prev = newHead;
            head = newHead;
        }
        size++;
        retVal = true;

        return retVal;
    }
    bool insertLast(int value) {
        bool retVal = false;

        if (isFull() == true) {
            return retVal;
        }

        if (head == NULL) {
            head = new Node(value);
            rear = head;
        } else {
            Node* newNode = new Node(value, NULL, rear);
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        retVal = true;

        return retVal;
    }
    bool deleteFront() {
        bool retVal = false;

        if (isEmpty() == true) {
            return retVal;
        }

        if (size == 1) {
            head = NULL;
            rear = NULL;
        } else {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        size--;
        retVal = true;

        return retVal;
    }
    bool deleteLast() {
        bool retVal = false;

        if (isEmpty() == true) {
            return retVal;
        }

        if (size == 1) {
            head = NULL;
            rear = NULL;
        } else {
            Node* prevNode = rear->prev;
            delete rear;
            rear = prevNode;
        }
        size--;
        retVal = true;

        return retVal;
    }
    int getFront() {
        int retVal = -1;  // Returns -1 if the deque is empty.

        if (isEmpty() == false) {
            retVal = head->val;
        }

        return retVal;
    }
    int getRear() {
        int retVal = -1;  // Returns -1 if the deque is empty.

        if (isEmpty() == false) {
            retVal = rear->val;
        }

        return retVal;
    }
    bool isEmpty() {
        bool retVal = false;

        if (size == 0) {
            retVal = true;
        }

        return retVal;
    }
    bool isFull() {
        bool retVal = false;

        if (size == capacity) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> values;
    };
    vector<subject> testData{{{"MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront", "getRear",
                               "isFull", "deleteLast", "insertFront", "getFront"},
                              {{3}, {1}, {2}, {3}, {4}, {}, {}, {}, {4}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront",
     *  "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
     *  [[3], [1], [2], [3], [4], [], [], [], [4], []]
     *  Output
     *  [null, true, true, true, false, 2, true, true, true, 4]
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
                cout << (k == 0 ? "" : ",") << testData[i].values[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        MyCircularDeque cMyCircularDeque(testData[i].values[0][0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ",");
            if (testData[i].methods[j].compare("MyCircularDeque") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("insertFront") == 0) {
                bool retVal = cMyCircularDeque.insertFront(testData[i].values[j][0]);
                cout << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("insertLast") == 0) {
                bool retVal = cMyCircularDeque.insertLast(testData[i].values[j][0]);
                cout << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("deleteFront") == 0) {
                bool retVal = cMyCircularDeque.deleteFront();
                cout << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("deleteLast") == 0) {
                bool retVal = cMyCircularDeque.deleteLast();
                cout << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("getFront") == 0) {
                int retVal = cMyCircularDeque.getFront();
                cout << retVal;
            } else if (testData[i].methods[j].compare("getRear") == 0) {
                int retVal = cMyCircularDeque.getRear();
                cout << retVal;
            } else if (testData[i].methods[j].compare("isEmpty") == 0) {
                bool retVal = cMyCircularDeque.isEmpty();
                cout << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("isFull") == 0) {
                bool retVal = cMyCircularDeque.isFull();
                cout << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
