// n => num bags => cookies.size()
// Time complexity : O(k ^ n)
// Space complexity : O(n + k)
class Solution {
public:
    int
    distributeCookies(vector<int>& cookies, int k) {
        if (0 == k) {
            // Base case of nil children
            return 0;
        }
        
        // Initialize
        _nBags = cookies.size();
        _nCookiesPerChildV.resize(k, 0);
        _minUnfairness = numeric_limits<int>::max();
        
        // Distribute cookies via DFS and backtracking 
        distributeCookiesDfsHelper(cookies, 0, k);
        
        return _minUnfairness;
    }
    
private:
    
    void
    distributeCookiesDfsHelper(
        vector<int>& cookies, int currBagId, int nChildren) {
        
        if (currBagId == _nBags) {
            // All cookie bags have been fully allocated for the current distribution
            // Compute the unfairness of the current cookie distribution
            int currUnfairness =
                *max_element(_nCookiesPerChildV.begin(), _nCookiesPerChildV.end());
            // Update the minimum unfairness seen so far
            _minUnfairness = min(_minUnfairness, currUnfairness);
            
            return;
        }
        
        auto nCookiesInCurrBag = cookies[currBagId];
        // Iterate over each child in sequence. Determine the unfairness
        // by attempting to distribute all the cookies in current bag to
        // each child, taking back the cookies and so on
        for (int childId = 0; childId < nChildren; ++childId) {
            // Distribute all the cookies in the current bag to the child 'childId'
            _nCookiesPerChildV[childId] += nCookiesInCurrBag;
            // Move on to next bag of cookies and determine the unfairness with
            // the above distribution recursively
            auto nextBagId = currBagId + 1;
            distributeCookiesDfsHelper(cookies, nextBagId, nChildren);
            // Backtrack and take back the cookies given from the current
            // bag to the child 'childId'
            _nCookiesPerChildV[childId] -= nCookiesInCurrBag;
        }
    }
    
    // Data members
    // Array tracking the number of cookies alloted to each child during backtracking
    vector<int> _nCookiesPerChildV;
    int _nBags;
    // Tracks the min unfairness amongst all distributions seen so far
    int _minUnfairness;
};
