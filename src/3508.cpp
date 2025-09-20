#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Router {
   public:
    int memLimit = 0;
    int length = 0;
    set<tuple<int, int, int>> isExist;
    unordered_map<int, deque<int>> sameDestQue;
    deque<tuple<int, int, int>> que;

    Router(int memoryLimit) {
        //
        memLimit = memoryLimit;
    }
    bool addPacket(int source, int destination, int timestamp) {
        bool retVal = false;

        tuple<int, int, int> packet = make_tuple(source, destination, timestamp);
        if (isExist.find(packet) != isExist.end()) {
            return retVal;
        }

        if (length == memLimit) {
            forwardPacket();
        }
        length++;
        que.push_back(packet);
        sameDestQue[destination].push_back(timestamp);
        isExist.insert(packet);
        retVal = true;

        return retVal;
    }
    vector<int> forwardPacket() {
        vector<int> retVal;

        if (que.empty() == false) {
            tuple<int, int, int> packet = que.front();
            que.pop_front();
            retVal = vector<int>{get<0>(packet), get<1>(packet), get<2>(packet)};
            isExist.erase(packet);
            sameDestQue[retVal[1]].pop_front();
            length--;
        }

        return retVal;
    }
    int getCount(int destination, int startTime, int endTime) {
        int retVal = 0;

        auto pos1 = lower_bound(sameDestQue[destination].begin(), sameDestQue[destination].end(), startTime);
        auto pos2 = upper_bound(sameDestQue[destination].begin(), sameDestQue[destination].end(), endTime);
        retVal = pos2 - pos1;

        return retVal;
    }
};
/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<int> memoryLimit;
        vector<int> source;
        vector<int> destination;
        vector<int> timestamp;
        vector<int> startTime;
        vector<int> endTime;
    };
    vector<subject> testData{{{"Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket",
                               "forwardPacket", "addPacket", "getCount"},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 1, 2, 1, 3, 4, 0, 5, 0},
                              {0, 4, 5, 4, 5, 5, 0, 2, 5},
                              {0, 90, 90, 90, 95, 105, 0, 110, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 100},
                              {0, 0, 0, 0, 0, 0, 0, 0, 110}},
                             {{"Router", "addPacket", "forwardPacket", "forwardPacket"},
                              {2, 0, 0, 0},
                              {0, 7, 0, 0},
                              {0, 4, 0, 0},
                              {0, 90, 0, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:
     *  ["Router","addPacket","addPacket","addPacket","addPacket","addPacket","forwardPacket","addPacket","getCount"]
     *  [[3],[1,4,90],[2,5,90],[1,4,90],[3,5,95],[4,5,105],[],[5,2,110],[5,100,110]]
     *  Output:
     *  [null,true,true,false,true,true,[2,5,90],true,1]
     *
     *  Input:
     *  ["Router","addPacket","forwardPacket","forwardPacket"]
     *  [[2],[7,4,90],[],[]]
     *  Output:
     *  [null,true,[7,4,90],[]]
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
            if (testData[i].methods[j].compare("Router") == 0) {
                cout << (j == 0 ? "" : ", ") << "[" << testData[i].memoryLimit[j] << "]";
            } else if (testData[i].methods[j].compare("addPacket") == 0) {
                cout << (j == 0 ? "" : ", ") << "[" << testData[i].source[j] << ", " << testData[i].destination[j]
                     << ", " << testData[i].timestamp[j] << "]";
            } else if (testData[i].methods[j].compare("forwardPacket") == 0) {
                cout << (j == 0 ? "" : ", ") << "[" << "]";
            } else if (testData[i].methods[j].compare("getCount") == 0) {
                cout << (j == 0 ? "" : ", ") << "[" << testData[i].destination[j] << ", " << testData[i].startTime[j]
                     << ", " << testData[i].endTime[j] << "]";
            }
        }
        cout << "]\n";

        Router cRouter(testData[i].memoryLimit[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("Router") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addPacket") == 0) {
                bool retVal =
                    cRouter.addPacket(testData[i].source[j], testData[i].destination[j], testData[i].timestamp[j]);
                cout << (j == 0 ? "" : ", ") << (retVal == true ? "true" : "false");
            } else if (testData[i].methods[j].compare("forwardPacket") == 0) {
                vector<int> retVal = cRouter.forwardPacket();
                cout << (j == 0 ? "" : ", ") << "[";
                for (long unsigned int j = 0; j < retVal.size(); ++j) {
                    cout << ((j == 0) ? "" : ",") << retVal[j];
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("getCount") == 0) {
                int retVal =
                    cRouter.getCount(testData[i].destination[j], testData[i].startTime[j], testData[i].endTime[j]);
                cout << (j == 0 ? "" : ", ") << retVal;
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
