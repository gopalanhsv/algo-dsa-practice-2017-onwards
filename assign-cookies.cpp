// n => s.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    findContentChildren(vector<int>& g, vector<int>& s) {
        
        // Adopt the greedy approach of attempting to give a child (from amongst
        // those yet to be assigned cookies) with the least greed, the smallest sized
        // cookie (from amongst the unassigned cookies)
        // The above is easily accomplished by sorting both the greed factor
        // and child size arrays in ascending order; and doing the cookie assignment
        
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int nCookies = s.size();
        int cookieIdx = 0;
        int nContentChildren = 0;
        // Iterate through child greed factor in ascending order
        for (auto & minCookieSzForChild : g) {
            
            // Attempt to assign the current child with smallest
            // cookie which can be given to it to satiate its greed
            while ((cookieIdx < nCookies) &&
                   (s[cookieIdx] < minCookieSzForChild)) {
                ++cookieIdx;
            }
            
            if (cookieIdx == nCookies) {
                // No more cookies can be assigned
                break;
            }
            
            // Cookie at 'cookieIdx' assigned;
            // advance to next child and cookie
            ++nContentChildren;
            ++cookieIdx;
        }
        
        return nContentChildren;
    }
};
