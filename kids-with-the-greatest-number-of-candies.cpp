// Time Complexity : O(candies.size())
// Space Complexity : O(1)

class Solution {
public:
    vector<bool>
    kidsWithCandies(vector<int>& candies, int extraCandies) {
    
        // Find the max number of candies any kid has
        int maxCandies = *(max_element(candies.begin(), candies.end()));

        int nKids = candies.size();
        vector<bool> greatestNumCandiesV(nKids, false);
        // When all the extra candies are given to a single kid; it will end
        // up with the greatest number of candies only if its total is g.e
        // to the max candies
        // (i.e candies[i] + extraCandies >= maxCandies
        // OR candies[i] >= maxCandies - extraCandies)
        // In other words, those would be the kids with number of
        // original candies exceeding the following threshold
        int threshold = maxCandies - extraCandies;
        for (int i = 0; i != nKids; ++i) {
            if (candies[i] >= threshold) {
                greatestNumCandiesV[i] = true;
            }
        }
        
        return greatestNumCandiesV;
    }
};
