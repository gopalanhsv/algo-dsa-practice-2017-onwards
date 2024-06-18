// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minimumChairs(string s) {
        int minChairs = 0;
        int nChairsInUse = 0;
        // Iterate over the events in sequence
        for (auto & c : s) {
            if (c == 'E') {
                // Person entry => increment chairs in use and update min chairs reqd
                minChairs = max(++nChairsInUse, minChairs);
            } else {
                // Person exit => decrement chairs in use
                --nChairsInUse;
            }
        }
        
        return minChairs;
    }
};
