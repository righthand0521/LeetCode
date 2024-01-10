#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Food {
   public:
    int foodRating;   // Store the food's rating.
    string foodName;  // Store the food's name.

    Food(int foodRating, string foodName) {
        this->foodRating = foodRating;
        this->foodName = foodName;
    }
    // Overload the less than operator for comparison
    bool operator<(const Food& other) const {
        // If food ratings are same sort on the basis of their name. (lexographically smaller name food will be on top)
        if (foodRating == other.foodRating) {
            return foodName > other.foodName;
        }
        // Sort on the basis of food rating. (bigger rating food will be on top)
        return foodRating < other.foodRating;
    }
};
class FoodRatings {
    unordered_map<string, int> foodRatingMap;      // Map food with its rating.
    unordered_map<string, string> foodCuisineMap;  // Map food with cuisine it belongs to.
    // Store all food of a cusine in priority queue (to sort them on ratings/name)
    // Priority queue element -> Food: (foodRating, foodName)
    unordered_map<string, priority_queue<Food>> cuisineFoodMap;

   public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int foodsSize = foods.size();
        for (int i = 0; i < foodsSize; ++i) {
            // Store 'rating' and 'cuisine' of current 'food' in 'foodRatingMap' and 'foodCuisineMap' maps.
            foodRatingMap[foods[i]] = ratings[i];
            foodCuisineMap[foods[i]] = cuisines[i];
            // Insert the '(rating, name)' element in current cuisine's priority queue.
            cuisineFoodMap[cuisines[i]].push(Food(ratings[i], foods[i]));
        }
    }
    void changeRating(string food, int newRating) {
        // Update food's rating in 'foodRating' map.
        foodRatingMap[food] = newRating;
        // Insert the '(new rating, name)' element in respective cuisine's priority queue.
        auto cuisineName = foodCuisineMap[food];
        cuisineFoodMap[cuisineName].push(Food(newRating, food));
    }
    string highestRated(string cuisine) {
        // Get the highest rated 'food' of 'cuisine'.
        auto highestRated = cuisineFoodMap[cuisine].top();

        // If latest rating of 'food' doesn't match with 'rating' on which it was sorted in priority queue,
        // then we discard this element of the priority queue.
        while (foodRatingMap[highestRated.foodName] != highestRated.foodRating) {
            cuisineFoodMap[cuisine].pop();
            highestRated = cuisineFoodMap[cuisine].top();
        }
        // Return name of the highest rated 'food' of 'cuisine'.
        return highestRated.foodName;
    }
};
/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<vector<string>> foods;
        vector<vector<string>> cuisines;
        vector<vector<int>> ratings;
        vector<string> food;
        vector<int> newRating;
        vector<string> cuisine;
    };
    vector<subject> testData{
        {{"FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating",
          "highestRated"},
         {{"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"}, {}, {}, {}, {}, {}, {}},
         {{"korean", "japanese", "japanese", "greek", "japanese", "korean"}, {}, {}, {}, {}, {}, {}},
         {{9, 12, 8, 15, 14, 7}, {}, {}, {}, {}, {}, {}},
         {{}, {}, {}, {"sushi"}, {}, {"ramen"}, {}},
         {{}, {}, {}, {16}, {}, {16}, {}},
         {{}, {"korean"}, {"japanese"}, {}, {"japanese"}, {}, {"japanese"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating", "highestRated"]
     *  [[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"],
     *  ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]],
     *  ["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16], ["japanese"]]
     *  Output
     *  [null, "kimchi", "ramen", null, "sushi", null, "ramen"]
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
            if (testData[i].methods[j].compare("FoodRatings") == 0) {
                cout << "[";
                for (long unsigned int k = 0; k < testData[i].foods[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ");
                    cout << "\"" << testData[i].foods[j][k] << "\"";
                }
                cout << "], [";
                for (long unsigned int k = 0; k < testData[i].cuisines[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ");
                    cout << "\"" << testData[i].cuisines[j][k] << "\"";
                }
                cout << "], [";
                for (long unsigned int k = 0; k < testData[i].ratings[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ");
                    cout << testData[i].ratings[j][k];
                }
                cout << "]";
            } else if (testData[i].methods[j].compare("changeRating") == 0) {
                cout << "\"" << testData[i].food[j] << "\"" << ',' << testData[i].newRating[j];
            } else if (testData[i].methods[j].compare("highestRated") == 0) {
                cout << "\"" << testData[i].cuisine[j] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        FoodRatings cFoodRatings(testData[i].foods[0], testData[i].cuisines[0], testData[0].ratings[0]);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("FoodRatings") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("changeRating") == 0) {
                cFoodRatings.changeRating(testData[i].food[j], testData[i].newRating[j]);
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("highestRated") == 0) {
                string retVal = cFoodRatings.highestRated(testData[i].cuisine[j]);
                cout << (j == 0 ? "" : ", ") << "\"" << retVal << "\"";
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
