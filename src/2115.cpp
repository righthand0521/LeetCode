#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients,
                                  vector<string>& supplies) {
        vector<string> retVal;

        int recipesSize = recipes.size();

        unordered_set<string> availableSupplies;  // Store available supplies
        // Initialize available supplies
        for (string& supply : supplies) {
            availableSupplies.insert(supply);
        }

        unordered_map<string, int> recipeToIndex;  // Map recipe to its index
        // Create recipe to index mapping
        for (int idx = 0; idx < recipesSize; idx++) {
            recipeToIndex[recipes[idx]] = idx;
        }

        unordered_map<string, vector<string>> dependencyGraph;  // Map ingredient to recipes that need it
        vector<int> inDegree(recipesSize, 0);  // Count of non-supply ingredients needed for each recipe
        // Build dependency graph
        for (int recipeIdx = 0; recipeIdx < recipesSize; recipeIdx++) {
            for (string& ingredient : ingredients[recipeIdx]) {
                if (availableSupplies.count(ingredient) != 0) {
                    continue;
                }
                // Add edge: ingredient -> recipe
                dependencyGraph[ingredient].push_back(recipes[recipeIdx]);
                inDegree[recipeIdx]++;
            }
        }

        // Start with recipes that only need supplies
        queue<int> queue;
        for (int recipeIdx = 0; recipeIdx < recipesSize; recipeIdx++) {
            if (inDegree[recipeIdx] == 0) {
                queue.push(recipeIdx);
            }
        }

        // Process recipes in topological order
        while (queue.empty() == false) {
            int recipeIdx = queue.front();
            queue.pop();

            string recipe = recipes[recipeIdx];
            retVal.push_back(recipe);

            // Skip if no recipes depend on this one
            if (dependencyGraph.count(recipe) == 0) {
                continue;
            }

            // Update recipes that depend on current recipe
            for (string& dependentRecipe : dependencyGraph[recipe]) {
                if (--inDegree[recipeToIndex[dependentRecipe]] == 0) {
                    queue.push(recipeToIndex[dependentRecipe]);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> recipes;
        vector<vector<string>> ingredients;
        vector<string> supplies;
    };
    vector<subject> testData{
        {{"bread"}, {{"yeast", "flour"}}, {"yeast", "flour", "corn"}},
        {{"bread", "sandwich"}, {{"yeast", "flour"}, {"bread", "meat"}}, {"yeast", "flour", "meat"}},
        {{"bread", "sandwich", "burger"},
         {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}},
         {"yeast", "flour", "meat"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
     *  Output: ["bread"]
     *
     *  Input: recipes = ["bread","sandwich"],
     *  ingredients = [["yeast","flour"],["bread","meat"]],
     *  supplies = ["yeast","flour","meat"]
     *  Output:["bread","sandwich"]
     *
     *  Input: recipes = ["bread","sandwich","burger"],
     *  ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]],
     *  supplies = ["yeast","flour","meat"]
     *  Output: ["bread","sandwich","burger"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: recipes = [";
        for (long unsigned int j = 0; j < testData[i].recipes.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].recipes[j] << "\"";
        }
        cout << "], ingredients = [";
        for (long unsigned int j = 0; j < testData[i].ingredients.size(); ++j) {
            for (long unsigned int k = 0; k < testData[i].ingredients[j].size(); ++k) {
                cout << ((j == 0) ? "" : ",") << "\"" << testData[i].ingredients[j][k] << "\"";
            }
        }
        cout << "], supplies = [";
        for (long unsigned int j = 0; j < testData[i].supplies.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].supplies[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.findAllRecipes(testData[i].recipes, testData[i].ingredients, testData[i].supplies);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
