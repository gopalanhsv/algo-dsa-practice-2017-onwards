// Not all states computed
// For n >= 5000 O(1)
// For n < 5000 at most O(5000/25 * 5000/25) states computed which is O(1)
// Space requirement is at most  O(5000/25 * 5000/25) states which is O(1)
// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    double
    soupServings(int n) {
        if (n >= 5000) {
            // When quantity of soup and hence number of servings are very large,
            // chances of soup A depleting prior to soup B is sure-shot because :-
            // 2 out of 4 options choosen (with identical likelihood) in each step
            // result in soup A getting depleted at the faster rate compared to soup B.
            // 1 out of 4 options choosen (with identical likelihood) in each step
            // result in soup A getting depleted at the same rate compared to soup B.
            // So by Strongs law of large numbers (large n), A getting depleted
            // faster OR same time as B is 100%
            return 1.0;
        }
        
        // Explore all possible options of serving the soup recursively via top down DP
        return probabilityViaTopDownMemoization(n);
    }
    
private:
    
    double
    probViaTopDownMemoRecursive(int qtyA, int qtyB) {
        
        // Base/termination cases
        if ((0 == qtyA) && (0 != qtyB)) {
            // Soup A depleted prior to B. Need the full probability
            return 1.0;
        } else if ((0 == qtyA) && (0 == qtyB)) {
            // Soup A and B depleted at same time
            // Need half the probability they empty at same time
            return 0.5;
        } else if ((0 != qtyA) && (0 == qtyB)) {
            // Soup A depleted prior to B. Event not allowed
            // and this probability is not required in final computation
            return 0;
        }
        
        // Some quantity of both soup A and B remain
        
        if (0 != _probabilityTbl[qtyA][qtyB]) {
            // The state was reached and computed earlier. Return
            // the cached earlier computed result
            return _probabilityTbl[qtyA][qtyB];
        }
        
        // Compute the result probability for state (qtyA, qtyB) recursively by determining
        // the probability for the 4 different equally likely operations possible
        double prob = 0.0;
        // 100 ml of soup A and 0 ml of soup B
        prob += 0.25 * probViaTopDownMemoRecursive(qtyA - min(qtyA, 100), qtyB);
        // 75 ml of soup A and 25 ml of soup B
        prob += 0.25 * probViaTopDownMemoRecursive(qtyA - min(qtyA, 75), qtyB - min(qtyB, 25));
        // 50 ml of soup A and 50 ml of soup B
        prob += 0.25 * probViaTopDownMemoRecursive(qtyA - min(qtyA, 50), qtyB - min(qtyB, 50));
        // 25 ml of soup A and 75 ml of soup B
        prob += 0.25 * probViaTopDownMemoRecursive(qtyA - min(qtyA, 25), qtyB - min(qtyB, 75));

        // Cache the result and return
        _probabilityTbl[qtyA][qtyB] = prob;
        return prob;
    }
    
    double
    probabilityViaTopDownMemoization(int n) {
        return probViaTopDownMemoRecursive(n, n);
    }
    
    // Data members
    // Cache table for probabilities
    // _probabilityTbl[X][Y] gives the probability if soup A empties first
    // plus half the probability that soup A & B empty at the same time when
    // the serving process commences with X ml of soup A and Y ml of soup B
    unordered_map<int, unordered_map<int, double> > _probabilityTbl;
};
