#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Represents a query with its original index and value
class Query {
   public:
    int index;
    int value;
    Query(int i, int v) : index(i), value(v) {}
};
bool operator<(const Query& a, const Query& b) {
    //
    return a.value < b.value;
}
// Represents a cell in the grid with row index, column index, and value
class Cell {
   public:
    int row;
    int col;
    int value;
    Cell(int r, int c, int v) : row(r), col(c), value(v) {}
};
bool operator<(const Cell& a, const Cell& b) {
    //
    return a.value < b.value;
}
// Union-Find to track connected components
class UnionFind {
   private:
    vector<int> parent;
    vector<int> size;

   public:
    // Initialize all parents to -1 (disjoint sets) and each component starts with size 1
    UnionFind(int n) : parent(vector<int>(n, -1)), size(vector<int>(n, 1)) {}
    int find(int node) {  // Find with path compression
        int retVal = 0;

        if (parent[node] < 0) {  // If negative, it's the root
            retVal = node;
        } else {
            // Path compression
            retVal = (parent[node] = find(parent[node]));
        }

        return retVal;
    }
    bool union_nodes(int nodeA, int nodeB) {  // Union by size (merge smaller tree into larger tree)
        int retVal = true;

        int rootA = find(nodeA);
        int rootB = find(nodeB);
        if (rootA == rootB) {  // Already connected
            retVal = false;
            return retVal;
        }

        if (size[rootA] > size[rootB]) {
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
        } else {
            parent[rootA] = rootB;
            size[rootB] += size[rootA];
        }

        return retVal;
    }
    int getSize(int node) {  // Get the size of the component containing a given node
        int retVal = size[find(node)];

        return retVal;
    }
};
class Solution {
   private:
    const vector<int> rowDirections = {0, 0, 1, -1};  // Right, Left, Down, Up
    const vector<int> colDirections = {1, -1, 0, 0};  // Corresponding column moves

   public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        vector<int> retVal;

        int rowSize = grid.size();
        int colSize = grid[0].size();
        int queriesSize = queries.size();

        retVal.resize(queriesSize);

        // Store queries with their original indices to maintain result order
        vector<Query> sortedQueries;
        for (int i = 0; i < queriesSize; i++) {
            sortedQueries.push_back(Query(i, queries[i]));
        }
        sort(sortedQueries.begin(), sortedQueries.end());  // Sort queries in ascending order

        // Store all grid cells and sort them by value
        vector<Cell> sortedCells;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                sortedCells.push_back(Cell(row, col, grid[row][col]));
            }
        }
        sort(sortedCells.begin(), sortedCells.end());  // Sort cells by value

        // Union-Find to track connected components
        int totalCells = rowSize * colSize;
        UnionFind uf = UnionFind(totalCells);

        int cellIndex = 0;
        // Process queries in sorted order
        for (Query query : sortedQueries) {
            // Process cells whose values are smaller than the current query value
            while (cellIndex < totalCells && sortedCells[cellIndex].value < query.value) {
                int row = sortedCells[cellIndex].row;
                int col = sortedCells[cellIndex].col;
                int cellId = row * colSize + col;  // Convert 2D position to 1D index
                // Merge the current cell with its adjacent cells that have already been processed
                for (int direction = 0; direction < 4; direction++) {
                    int newRow = row + rowDirections[direction];
                    int newCol = col + colDirections[direction];
                    int newCellId = newRow * colSize + newCol;  // Convert 2D position to 1D index
                    // Check if the new cell is within bounds and its value is smaller than the query value
                    if ((newRow < 0) || (newRow >= rowSize) || (newCol < 0) || (newCol >= colSize)) {
                        continue;
                    } else if (grid[newRow][newCol] < query.value) {
                        uf.union_nodes(cellId, newCellId);
                    }
                }
                cellIndex++;
            }

            // Get the size of the connected component containing the top-left cell (0,0)
            retVal[query.index] = (query.value > grid[0][0]) ? uf.getSize(0) : 0;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
        vector<int> queries;
    };
    vector<subject> testData{{{{1, 2, 3}, {2, 5, 7}, {3, 5, 1}}, {5, 6, 2}}, {{{5, 2, 1}, {1, 1, 2}}, {3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
     *  Output: [5,8,1]
     *
     *  Input: grid = [[5,2,1],[1,1,2]], queries = [3]
     *  Output: [0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].queries[j];
        }
        cout << "]\n";

        answer = cSolution.maxPoints(testData[i].grid, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
