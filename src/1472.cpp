#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class BrowserHistory {
   private:
    vector<string> pageList;
    int index;

   public:
    BrowserHistory(string homepage) {
        pageList.push_back(homepage);
        index = 0;
    }
    void visit(string url) {
        pageList.erase(pageList.begin() + index + 1, pageList.end());
        pageList.push_back(url);

        ++index;
    }
    string back(int steps) {
        index = max(0, index - steps);

        return pageList[index];
    }
    string forward(int steps) {
        index = min(index + steps, (int)pageList.size() - 1);

        return pageList[index];
    }
};
/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

int main(int argc, char** argv) {
#define DISPLAY_NULL (-1)
    struct subject {
        vector<string> methods;
        vector<string> value1;
        vector<int> value2;
    };
    vector<subject> testData{
        {{"BrowserHistory", "visit", "visit", "visit", "back", "back", "forward", "visit", "forward", "back", "back"},
         {"leetcode.com", "google.com", "facebook.com", "youtube.com", "", "", "", "linkedin.com", "", "", ""},
         {0, 0, 0, 0, 1, 1, 1, 0, 2, 2, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:
     *  ["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
     *  [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
     *  Output:
     *  [null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "\"" << testData[i].methods[j] << "\"";
        }
        cout << "]\n[";
        for (long unsigned int j = 0; j < testData[i].value1.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "[";
            if (testData[i].value2[j] == 0) {
                cout << "\"" << testData[i].value1[j] << "\"";
            } else {
                cout << testData[i].value2[j];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "Output\n[";
        BrowserHistory cSolution(testData[i].value1[0]);
        cout << "null";
        for (long unsigned int j = 1; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("visit") == 0) {
                cSolution.visit(testData[i].value1[j]);
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("back") == 0) {
                string retVal = cSolution.back(testData[i].value2[j]);
                cout << ((j == 0) ? "" : ", ") << "\"" << retVal << "\"";
            } else if (testData[i].methods[j].compare("forward") == 0) {
                string retVal = cSolution.forward(testData[i].value2[j]);
                cout << ((j == 0) ? "" : ", ") << "\"" << retVal << "\"";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
