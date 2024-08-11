#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class MinStack {
   private:
    stack<int> generalStack;
    stack<int> minStack;

   public:
    MinStack() {
        //
    }
    void push(int val) {
        generalStack.push(val);
        if (minStack.empty() == true) {
            minStack.push(val);
        } else {
            int minValue = minStack.top();
            minStack.push(min(val, minValue));
        }
    }
    void pop() {
        generalStack.pop();
        minStack.pop();
    }
    int top() {
        int retVal = generalStack.top();

        return retVal;
    }
    int getMin() {
        int retVal = minStack.top();

        return retVal;
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{{{"MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"},
                              {{}, {-2}, {0}, {-3}, {}, {}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MinStack","push","push","push","getMin","pop","top","getMin"]
     *  [[],[-2],[0],[-3],[],[],[],[]]
     *  Output
     *  [null,null,null,null,-3,null,0,-2]
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

        MinStack cMinStack;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("MinStack") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("push") == 0) {
                cMinStack.push(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("pop") == 0) {
                cMinStack.pop();
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("top") == 0) {
                int retVal = cMinStack.top();
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("getMin") == 0) {
                int retVal = cMinStack.getMin();
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
