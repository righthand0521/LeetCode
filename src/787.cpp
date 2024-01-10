#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
#define BELLMAN_FORD (1)  // https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm

   public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int retVal = -1;

#if (BELLMAN_FORD)
        vector<int> distance(n, numeric_limits<int>::max());
        distance[src] = 0;

        for (int i = 0; i <= k; ++i) {
            vector<int> temp(distance);
            for (auto& flight : flights) {
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];
                if (distance[from] != numeric_limits<int>::max()) {
                    temp[to] = min(temp[to], distance[from] + price);
                }
            }
            distance = temp;
        }

        if (distance[dst] != numeric_limits<int>::max()) {
            retVal = distance[dst];
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> flights;
        int src;
        int dst;
        int k;
    };
    vector<subject> testData{{4, {{0, 1, 100}, {1, 2, 300}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 0, 3, 1},
                             {3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1},
                             {3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", flights = [";
        for (long unsigned int j = 0; j < testData[i].flights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].flights[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].flights[j][k];
            }
            cout << "]";
        }
        cout << "], src = " << testData[i].src << ", dst = " << testData[i].dst << ", k = " << testData[i].k << "\n";

        answer = cSolution.findCheapestPrice(testData[i].n, testData[i].flights, testData[i].src, testData[i].dst,
                                             testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
