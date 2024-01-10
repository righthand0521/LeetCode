#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MyStack {
   public:
    queue<int> useQueue;
    queue<int> tempQueue;
    MyStack() {
        //
    }
    void push(int x) {
        tempQueue.push(x);
        while (useQueue.empty() == false) {
            tempQueue.push(useQueue.front());
            useQueue.pop();
        }
        swap(useQueue, tempQueue);
    }
    int pop() {
        int retVal = useQueue.front();

        useQueue.pop();

        return retVal;
    }
    int top() {
        int retVal = useQueue.front();

        return retVal;
    }
    bool empty() {
        bool retVal = false;

        if (useQueue.empty() == true) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{{{"MyStack", "push", "push", "top", "pop", "empty"}, {{}, {1}, {2}, {}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MyStack", "push", "push", "top", "pop", "empty"]
     *  [[], [1], [2], [], [], []]
     *  Output
     *  [null, null, null, 2, 2, false]
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

        MyStack cMyStack;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MyStack") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("push") == 0) {
                cMyStack.push(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("pop") == 0) {
                int retVal = cMyStack.pop();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("top") == 0) {
                int retVal = cMyStack.top();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("empty") == 0) {
                bool retVal = cMyStack.empty();
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
