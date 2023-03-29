// Time complexity 
// n => num dishes
// O(nlogn)
// Space complexity
// n => num dishes
// O(logn)

class Solution {
public:
    int
    maxSatisfaction(vector<int>& satisfaction) {
        // Since the dishes can be prepared in any order, to maximize the
        // like-time coeffiecient sum; adopt the greedy approach as follows:-
        // Prepare the dishes with higher satisfaction values after dishes
        // with lower satifaction values -- as this will increase the time
        // portion of coefficient value to be higher for the higher satisfaction
        // dish; contributing to a higher value of product towards the sum
        int nDishes = satisfaction.size();
        
        // Sort the dishes in the ascending order of satisfaction values
        // (to cook max satisfaction dishes at end as per the greedy approach)
        sort(satisfaction.begin(), satisfaction.end());
        
        // Move from dishes with higher satisfaction values to lower satisfaction
        // values; selecting the dishes with higher satisfaction values to be
        // cooked later after those with lower satisfaction values.
        // Keep doing this till a dish is reached (to be cooked first) s.t. adding
        // the dish (with least satisfaction value) reduces the total like-time
        // coefficient sum. Discard all the dishes from this point to the left
        // (with lower satisfaction values) as adding these dishes will reduce
        // the overall customer satifaction
        
        // Sum of like-time coefficient vals from prev selected dish to final 
        // dish to right
        long suffixLikeTimeCoeffSum = 0;
        // Sum of satisfaction vals from prev selected dish to final 
        // dish to right (with progressively higher satisfaction vals)
        long suffixSatisfactionSum = 0;
        
        // Iterate over dishes in descending order of their satisfaction vals
        for (int dId = nDishes - 1; dId >= 0; --dId) {
            // Satisfaction value for current dish
            auto & currSatisfaction = satisfaction[dId];
            
            // Compute the sum of like-time coefficients if current
            // dish and the succeeding dishes are selected (i.e. current
            // dish at 'dId' is the first to be cooked followed by all
            // those in range [dId + 1, nDishes - 1] in succession)
            long newLikeTimeCoeffSum =
                currSatisfaction + suffixLikeTimeCoeffSum + suffixSatisfactionSum;
            
            if (newLikeTimeCoeffSum < suffixLikeTimeCoeffSum) {
                // Selecting current dish onwards(i.e with lower satisfaction vals)
                // will reduce the like-time coefficient sum. So discard from
                // this dish onwards
                break;
            }
            
            // Current dish is selected (as first dish to be cooked for time being)
            suffixLikeTimeCoeffSum = newLikeTimeCoeffSum;
            suffixSatisfactionSum += currSatisfaction;
        }
        
        return suffixLikeTimeCoeffSum;
    }
};
