#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class MyQueue {
   private:
    stack<int> stackQueue;
    stack<int> stackTmp;

   public:
    MyQueue() {}
    void push(int x) {
        while (empty() == false) {
            stackTmp.push(pop());
        }

        stackQueue.push(x);

        while (stackTmp.empty() == false) {
            stackQueue.push(stackTmp.top());
            stackTmp.pop();
        }
    }
    int pop() {
        int retVal = 0;

        if (empty() == false) {
            retVal = stackQueue.top();
            stackQueue.pop();
        }

        return retVal;
    }
    int peek() {
        int retVal = stackQueue.top();

        return retVal;
    }
    bool empty() {
        bool retVal = stackQueue.empty();

        return retVal;
    }
};
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<int> num;
    };
    vector<subject> testData{{{"MyQueue", "push", "push", "peek", "pop", "empty"}, {0, 1, 2, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyQueue", "push", "push", "peek", "pop", "empty"]
     *  [[], [1], [2], [], [], []]
     *  Output
     *  [null, null, null, 1, 1, false]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        MyQueue cMyQueue;

        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].num.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].num[j] != 0) {
                cout << testData[i].num[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MyQueue") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("push") == 0) {
                cMyQueue.push(testData[i].num[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("pop") == 0) {
                int retVal = cMyQueue.pop();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("peek") == 0) {
                int retVal = cMyQueue.peek();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("empty") == 0) {
                bool retVal = cMyQueue.empty();
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
