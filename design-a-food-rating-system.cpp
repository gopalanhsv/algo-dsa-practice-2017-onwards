// f => number of foods
// Time complexity :
// Constructor : O(f x log f)
// changeRating() : O(n x log f), n => num calls to function
// highestRated() : O(log f), n => num calls to function

// Space complexity : O(f)

class FoodRatings {
public:
    typedef struct _FoodInfoT {
        string cuisine;
        int rating;
    } FoodInfoT;
    
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int nFoods = foods.size();
        // Iterate over each food item
        for (int i = 0; i != nFoods; ++i) {
            // Add the food item data to the 2 tables maintiaing internal state
            auto & food = foods[i];
            auto & cuisine = cuisines[i];
            auto & rating = ratings[i];
            FoodInfoT fi;
            fi.cuisine = cuisine;
            fi.rating = rating;
            _foodToFoodInfoTbl[food] = fi;
            
            _cuisineToFoodRatingsTbl[cuisine][rating].insert(food);
        }
    }
    
    void
    changeRating(string food, int newRating) {
        // Get the cusuine + earlier rating for the food
        auto & foodInfo = _foodToFoodInfoTbl[food];
        auto & cuisine = foodInfo.cuisine;
        
        auto oldRating = foodInfo.rating;
        // Get the collection of foods against the foods' cuisine
        auto & cuisineFoodRatingsTbl = _cuisineToFoodRatingsTbl[cuisine];
        // Erase the food entry against the earlier rating from cuisine
        auto it = cuisineFoodRatingsTbl.find(oldRating);
        auto & cuisineOldRatingFoods = it->second;
        cuisineOldRatingFoods.erase(food);
        if (cuisineOldRatingFoods.empty()) {
            cuisineFoodRatingsTbl.erase(oldRating);
        }
        // Update the food rating
        foodInfo.rating = newRating;
        // Insert the food entry against the new rating in the cuisine table
        cuisineFoodRatingsTbl[newRating].insert(food);
    }
    
    string
    highestRated(string cuisine) {
        auto & foodRatingsTbl = _cuisineToFoodRatingsTbl[cuisine];
        auto & highestRatedFoods = (foodRatingsTbl.begin())->second;
        
        return *(highestRatedFoods.begin());
    }
    
private:

    // Data members
    // Hash table mapping each food item to its info (cuisine, current rating)
    unordered_map<string, FoodInfoT> _foodToFoodInfoTbl;
    // Hash table mapping each cuisine to the collection of food items which belong to
    // that cuisine. Food items of identical ratings for a cuisine are grouped
    // together in lexicographical ordering. Food groups of identical rating
    // are ordered in descending order of their respective ratings
    unordered_map<string, map<int, set<string>, greater<int> > > _cuisineToFoodRatingsTbl;
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
