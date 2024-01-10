#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ParkingSystem {
   public:
    int big;
    int medium;
    int small;
    ParkingSystem(int big, int medium, int small) {
        this->big = big;
        this->medium = medium;
        this->small = small;
    }
    bool addCar(int carType) {
        bool retVal = false;

        switch (carType) {
            case 1:
                if (this->big > 0) {
                    this->big -= 1;
                    retVal = true;
                }
                break;
            case 2:
                if (this->medium > 0) {
                    this->medium -= 1;
                    retVal = true;
                }
                break;
            case 3:
                if (this->small > 0) {
                    this->small -= 1;
                    retVal = true;
                }
                break;
            default:
                break;
        }

        return retVal;
    }
};
/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> methods;
        vector<vector<int>> carType;
    };
    vector<subject> testData{
        {{"ParkingSystem", "addCar", "addCar", "addCar", "addCart"}, {{1, 1, 0}, {1}, {2}, {3}, {1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
     *  [[1, 1, 0], [1], [2], [3], [1]]
     *  Output
     *  [null, true, true, false, false]
     */

    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].carType.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            for (long unsigned int k = 0; k < testData[i].carType[j].size(); ++k) {
                cout << (k == 0 ? "" : ", ") << testData[i].carType[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        ParkingSystem cParkingSystem(testData[i].carType[0][0], testData[i].carType[0][1], testData[i].carType[0][2]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("ParkingSystem") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addCar") == 0) {
                int retVal = cParkingSystem.addCar(testData[i].carType[j][0]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
