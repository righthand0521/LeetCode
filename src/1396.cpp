#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class UndergroundSystem {
   public:
    using Start = pair<string, int>;
    using StartEnd = pair<string, string>;
    using SumAndAmount = pair<int, int>;
    struct StartEndHash {
        int operator()(const StartEnd& x) const { return hash<string>()(x.first + x.second); }
    };
    unordered_map<int, Start> startInfo;
    unordered_map<StartEnd, SumAndAmount, StartEndHash> table;

    UndergroundSystem() {}
    void checkIn(int id, string stationName, int t) {
        //
        startInfo[id] = {stationName, t};
    }
    void checkOut(int id, string stationName, int t) {
        auto startTime = startInfo[id].second;
        table[{startInfo[id].first, stationName}].first += (t - startTime);
        table[{startInfo[id].first, stationName}].second++;
    }
    double getAverageTime(string startStation, string endStation) {
        double retVal;

        auto sum = table[{startStation, endStation}].first;
        auto amount = table[{startStation, endStation}].second;
        retVal = double(sum) / amount;

        return retVal;
    }
};
/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<int> id;
        vector<string> stationName;
        vector<int> t;
        vector<string> startStation;
        vector<string> endStation;
    };
    vector<subject> testData{
        {{"UndergroundSystem", "checkIn", "checkIn", "checkIn", "checkOut", "checkOut", "checkOut", "getAverageTime",
          "getAverageTime", "checkIn", "getAverageTime", "checkOut", "getAverageTime"},
         {0, 45, 32, 27, 45, 27, 32, 0, 0, 10, 0, 10, 0},
         {"", "Leyton", "Paradise", "Leyton", "Waterloo", "Waterloo", "Cambridge", "", "", "Leyton", "", "Waterloo",
          ""},
         {0, 3, 8, 10, 15, 20, 22, 0, 0, 24, 0, 38, 0},
         {"", "", "", "", "", "", "", "Paradise", "Leyton", "", "Leyton", "", "Leyton"},
         {"", "", "", "", "", "", "", "Cambridge", "Waterloo", "", "Waterloo", "", "Waterloo"}},
        {{"UndergroundSystem", "checkIn", "checkOut", "getAverageTime", "checkIn", "checkOut", "getAverageTime",
          "checkIn", "checkOut", "getAverageTime"},
         {0, 10, 10, 0, 5, 5, 0, 2, 2, 0},
         {"", "Leyton", "Paradise", "", "Leyton", "Paradise", "", "Leyton", "Paradise", ""},
         {0, 3, 8, 0, 10, 16, 0, 21, 30, 0},
         {"", "", "", "Leyton", "", "", "Leyton", "", "", "Leyton"},
         {"", "", "", "Paradise", "", "", "Paradise", "", "", "Paradise"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut",
     *  "checkOut","checkOut","getAverageTime","getAverageTime","checkIn",
     *  "getAverageTime","checkOut","getAverageTime"]
     *  [[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],
     *  [27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],
     *  ["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
     *  Output
     *  [null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
     *
     *  Input
     *  ["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn",
     *  "checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
     *  [[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],
     *  [5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
     *  Output
     *  [null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
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
            if (testData[i].methods[j].compare("UndergroundSystem") == 0) {
                cout << "";
            } else if (testData[i].methods[j].compare("checkIn") == 0) {
                cout << testData[i].id[j] << ',' << testData[i].stationName[j] << ',' << testData[i].t[j];
            } else if (testData[i].methods[j].compare("checkOut") == 0) {
                cout << testData[i].id[j] << ',' << testData[i].stationName[j] << ',' << testData[i].t[j];
            } else if (testData[i].methods[j].compare("getAverageTime") == 0) {
                cout << testData[i].startStation[j] << ',' << testData[i].endStation[j];
            }
            cout << "]";
        }
        cout << "]\n";

        UndergroundSystem cUndergroundSystem;
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("UndergroundSystem") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("checkIn") == 0) {
                cUndergroundSystem.checkIn(testData[i].id[j], testData[i].stationName[j], testData[i].t[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("checkOut") == 0) {
                cUndergroundSystem.checkOut(testData[i].id[j], testData[i].stationName[j], testData[i].t[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("getAverageTime") == 0) {
                double retVal =
                    cUndergroundSystem.getAverageTime(testData[i].startStation[j], testData[i].endStation[j]);
                cout.setf(ios::fixed);
                cout.precision(5);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
