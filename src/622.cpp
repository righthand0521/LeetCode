#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MyCircularQueue {
   private:
    vector<int> data;
    int head;
    int tail;
    int size;

   public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = -1;
        tail = -1;
        size = k;
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0;
        }
        tail = (tail + 1) % size;
        data[tail] = value;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }

    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() { return head == -1; }

    /** Checks whether the circular queue is full or not. */
    bool isFull() { return ((tail + 1) % size) == head; }
};

int main(int argc, char **argv) {
    cout << "Input" << endl;
    cout << "[\"MyCircularQueue\", \"enQueue\", \"enQueue\", \"enQueue\", \"enQueue\","
         << " \"Rear\", \"isFull\", \"deQueue\", \"enQueue\", \"Rear\"]" << endl;
    cout << "[[3], [1], [2], [3], [4], [], [], [], [4], []]" << endl;

    cout << "Output" << endl;
    cout << "[";
    MyCircularQueue obj = MyCircularQueue(3);
    cout << "null, ";
    cout << ((obj.enQueue(1) == true) ? "true" : "false") << ", ";
    cout << ((obj.enQueue(2) == true) ? "true" : "false") << ", ";
    cout << ((obj.enQueue(3) == true) ? "true" : "false") << ", ";
    cout << ((obj.enQueue(4) == true) ? "true" : "false") << ", ";
    cout << obj.Rear() << ", ";
    cout << ((obj.isFull() == true) ? "true" : "false") << ", ";
    cout << ((obj.deQueue() == true) ? "true" : "false") << ", ";
    cout << ((obj.enQueue(4) == true) ? "true" : "false") << ", ";
    cout << obj.Rear() << "";
    cout << "]" << endl;

    return EXIT_SUCCESS;
}
