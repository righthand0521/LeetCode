#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    void generateSequences(string& tiles, string current, vector<bool>& used, unordered_set<string>& sequences) {
        // Add current sequence to set
        sequences.insert(current);

        // Try adding each unused character to current sequence
        int tilesSize = tiles.size();
        for (int pos = 0; pos < tilesSize; ++pos) {
            if (used[pos] == true) {
                continue;
            }
            used[pos] = true;
            generateSequences(tiles, current + tiles[pos], used, sequences);
            used[pos] = false;
        }
    }

   public:
    int numTilePossibilities(string tiles) {
        int retVal = 0;

        int tilesSize = tiles.size();

        unordered_set<string> sequences;
        vector<bool> used(tilesSize, false);
        generateSequences(tiles, "", used, sequences);  // Generate all possible sequences including empty string
        retVal = sequences.size() - 1;                  // Subtract 1 to exclude empty string from count

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string tiles;
    };
    vector<subject> testData{{"AAB"}, {"AAABBC"}, {"V"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tiles = "AAB"
     *  Output: 8
     *
     *  Input: tiles = "AAABBC"
     *  Output: 188
     *
     *  Input: tiles = "V"
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tiles = \"" << testData[i].tiles << "\"\n";

        answer = cSolution.numTilePossibilities(testData[i].tiles);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
