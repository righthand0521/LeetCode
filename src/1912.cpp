#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class MovieRentingSystem {
   private:
    static constexpr auto pairHash = [fn = hash<int>()](const pair<int, int>& o) {
        return (fn(o.first) << 16) ^ fn(o.second);
    };
    unordered_map<pair<int, int>, int, decltype(pairHash)> t_price{0, pairHash};
    unordered_map<int, set<pair<int, int>>> t_valid;
    set<tuple<int, int, int>> t_rent;

   public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (const auto& entry : entries) {
            t_price[{entry[0], entry[1]}] = entry[2];
            t_valid[entry[1]].emplace(entry[2], entry[0]);
        }
    }
    vector<int> search(int movie) {
        vector<int> retVal;

        if (t_valid.count(movie) == 0) {
            return retVal;
        }

        auto it = t_valid[movie].begin();
        for (int i = 0; i < 5 && it != t_valid[movie].end(); ++i, ++it) {
            retVal.push_back(it->second);
        }

        return retVal;
    }
    void rent(int shop, int movie) {
        int price = t_price[{shop, movie}];
        t_valid[movie].erase({price, shop});
        t_rent.emplace(price, shop, movie);
    }
    void drop(int shop, int movie) {
        int price = t_price[{shop, movie}];
        t_valid[movie].emplace(price, shop);
        t_rent.erase({price, shop, movie});
    }
    vector<vector<int>> report() {
        vector<vector<int>> retVal;

        auto it = t_rent.begin();
        for (int i = 0; i < 5 && it != t_rent.end(); ++i, ++it) {
            retVal.emplace_back(initializer_list<int>{get<1>(*it), get<2>(*it)});
        }

        return retVal;
    }
};
/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<int> n;
        vector<vector<vector<int>>> entries;
        vector<int> shop;
        vector<int> movie;
    };
    vector<subject> testData{
        {{"MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"},
         {3, 0, 0, 0, 0, 0, 0},
         {{{{0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}}}, {}, {}, {}, {}, {}, {}},
         {0, 0, 0, 1, 0, 1, 0},
         {0, 1, 1, 2, 0, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"]
     *  [[3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2, 7], [2, 1, 5]]], [1], [0, 1], [1, 2], [], [1, 2], [2]]
     *  Output
     *  [null, [1, 0, 2], null, null, [[0, 1], [1, 2]], null, [0, 1]]
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
            cout << (j == 0 ? "" : ", ");
            if (testData[i].methods[j].compare("MovieRentingSystem") == 0) {
                cout << "[" << testData[i].n[j] << ", [";
                for (long unsigned int x = 0; x < testData[i].entries[j].size(); ++x) {
                    cout << (x == 0 ? "" : ", ") << "[";
                    for (long unsigned int y = 0; y < testData[i].entries[j][x].size(); ++y) {
                        cout << (y == 0 ? "" : ", ") << testData[i].entries[j][x][y];
                    }
                    cout << "]";
                }
                cout << "]";
                cout << "]";
            } else if (testData[i].methods[j].compare("search") == 0) {
                cout << "[" << testData[i].movie[j] << "]";
            } else if (testData[i].methods[j].compare("rent") == 0) {
                cout << "[" << testData[i].shop[j] << ", " << testData[i].movie[j] << "]";
            } else if (testData[i].methods[j].compare("report") == 0) {
                cout << "[]";
            } else if (testData[i].methods[j].compare("drop") == 0) {
                cout << "[" << testData[i].shop[j] << ", " << testData[i].movie[j] << "]";
            }
        }
        cout << "]\n";

        MovieRentingSystem cMovieRentingSystem(testData[i].n[0], testData[i].entries[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ");
            if (testData[i].methods[j].compare("MovieRentingSystem") == 0) {
                cout << "null";
            } else if (testData[i].methods[j].compare("search") == 0) {
                vector<int> retVal = cMovieRentingSystem.search(testData[i].movie[j]);
                cout << "[";
                for (long unsigned int k = 0; k < retVal.size(); ++k) {
                    cout << ((k == 0) ? "" : ",") << retVal[k];
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("rent") == 0) {
                cMovieRentingSystem.rent(testData[i].shop[j], testData[i].movie[j]);
                cout << "null";
            } else if (testData[i].methods[j].compare("report") == 0) {
                vector<vector<int>> retVal = cMovieRentingSystem.report();
                cout << "[";
                for (long unsigned int k = 0; k < retVal.size(); ++k) {
                    cout << ((k == 0) ? "" : ",") << "[";
                    for (long unsigned int l = 0; l < retVal[k].size(); ++l) {
                        cout << ((l == 0) ? "" : ",") << retVal[k][l];
                    }
                    cout << "]";
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("drop") == 0) {
                cMovieRentingSystem.drop(testData[i].shop[j], testData[i].movie[j]);
                cout << "null";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
