// n => Num pairs
// Time complexity: O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    findLongestChain(vector<vector<int>>& pairs) {
        if (pairs.size() <= 1) {
            // Base case of no/single pair
            return pairs.size();    
        }

        // Two pairs p1 (l1, r1) and p2 (l2, r2) can be chained iff r1 < l2
        // By definition of a pair, l1 < r1 & l2 < r2 
        // => Chaining is possible iff l1 < r1 < l2 < r2 i.e r1 < r2

        // Sort the pairs s.t. they are ordered in the non-decreasing order 'right' components;
        // and for pairs with same 'right' component order them in the non-decreasing order of
        // their 'left' components
        sort(pairs.begin(), pairs.end(),
            [&](const auto& p1, const auto& p2) {
                if (p1[1] == p2[1]) {
                    return p1[0] < p2[0];
                }
                return p1[1] < p2[1];
            });
        
        // Adopt the greedy approach of always choosing the next pair for the longest chain as
        // the one with least value 'right' (with a value of 'left' g.t 'right' of previously
        // selected pair) from amongst the pairs yet to be processed
        // The first pair in chain would be the one with least value of 'left' & 'right'
        auto chainLen = 1;
        auto prevPairRight = pairs[0][1];
        // Iterate over the pairs sequentially in the non-decreasing order of 'right' values
        for (auto & p : pairs) {
            auto & currPairLeft = p[0];
            if (currPairLeft > prevPairRight) {
                // Current pair satisfies the pair selection constraint as per greedy algo
                ++chainLen;
                auto & currPairRight = p[1];
                // Update the previous selected pair
                prevPairRight = currPairRight;
            }
        }
        
        return chainLen;
    }
};
