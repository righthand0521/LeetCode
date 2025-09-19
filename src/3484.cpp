#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Spreadsheet {
   private:
    unordered_map<string, int> cellValues;

   public:
    Spreadsheet(int) {}
    void setCell(string cell, int value) {
        //
        cellValues[cell] = value;
    }
    void resetCell(string cell) {
        //
        cellValues.erase(cell);
    }
    int getValue(string formula) {
        int retVal = 0;

        int i = formula.find('+');

        string cell1 = formula.substr(1, i - 1);
        if (isalpha(cell1[0])) {
            retVal = cellValues[cell1];
        } else {
            retVal = stoi(cell1);
        }

        string cell2 = formula.substr(i + 1);
        if (isalpha(cell2[0])) {
            retVal += cellValues[cell2];
        } else {
            retVal += stoi(cell2);
        }

        return retVal;
    }
};
/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<string> cell;
        vector<int> value;
    };
    vector<subject> testData{
        {{"Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"},
         {"", "=5+7", "A1", "=A1+6", "B2", "=A1+B2", "A1", "=A1+B2"},
         {3, 0, 10, 0, 15, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:
     *  ["Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"]
     *  [[3], ["=5+7"], ["A1", 10], ["=A1+6"], ["B2", 15], ["=A1+B2"], ["A1"], ["=A1+B2"]]
     *  Output:
     *  [null, 12, null, 16, null, 25, null, 15]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].cell[j] != "") {
                cout << "\"" << testData[i].cell[j] << "\"";
            }
            if ((testData[i].cell[j] != "") && (testData[i].value[j] != 0)) {
                cout << ", ";
            }
            if (testData[i].value[j] != 0) {
                cout << testData[i].value[j];
            }
            cout << "]";
        }
        cout << "]\n";

        Spreadsheet cSpreadsheet(testData[i].value[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("Spreadsheet") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("getValue") == 0) {
                int retVal = cSpreadsheet.getValue(testData[i].cell[j]);
                cout << (j == 0 ? "" : ", ") << retVal;
            } else if (testData[i].methods[j].compare("setCell") == 0) {
                cSpreadsheet.setCell(testData[i].cell[j], testData[i].value[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("resetCell") == 0) {
                cSpreadsheet.resetCell(testData[i].cell[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
