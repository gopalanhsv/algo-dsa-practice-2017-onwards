// Time complexity : O(min(limit, n))
// Space complexity : O(1)

class Solution {
public:
    long long
    distributeCandies(int n, int limit) {
        // Total 3 children. A child cannot be given more than max(limit, n) candies or
        // lesser than 0 candies. All 'n' candies have to be distributed with no leftovers
        // => 1st child is given 'i' candies in range (0, max(n, limit))
        //    2nd child is given 'j' candies in range (0, max(n, limit))
        //    3rd child is given 'n - i - j' candies in range (0, limit)
        //  => n - i - j >= 0 AND n - i - j <= limit
        //  => j <= n - i AND j >= n - i - limit
        //  => j >= max(0, n - i - limit) AND j <= min(limit, n - i)
        
        // The above implies that we can distribute the number of candies for 1st
        // and 2nd child as per the following:-
        // for 'i' candies given for 1st child in range (0, min(limit, n));
        // 'j' candies can be given for 2nd child with 'j' being in the
        // range [max(0, n - i - limit), min(limit, n - i)]
        // 3rd child gets 'n - i - j' candies by default with no choice
        
        // 1st child is distributed candies in 'i' ways [0, min(limit, n)]
        // 2nd child is ditributed candies in 'j' ways 
        // i.e max[min(limit, n - i) - [max(0, n - i - limit) + 1, 0] ways
        
        long long nWays = 0;
        // Iterate over all possible ways to distribute candies for first child
        for (auto nWaysFor1st = 0; nWaysFor1st <= min(n, limit); ++nWaysFor1st) {
            // Compute the number of ways to distribute candies for second child
            auto nWaysFor2nd =
                max(min(limit, n - nWaysFor1st) - max(0, n - nWaysFor1st - limit) + 1, 0);
            // Update total number of ways to include configuration
            // (nWaysFor1st, nWaysFor2nd)
            nWays += ((long long)nWaysFor2nd);
        }
        
        return nWays;
    }
};
