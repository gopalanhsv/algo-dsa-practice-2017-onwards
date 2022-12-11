class Solution {
public:
    vector<int>
    twoSum(vector<int>& v, int target) {
        
        typedef vector<int>::size_type vecSzT;
        
        vector<int> retV({-1, -1});
        
        // Hash table holding number and its location in the vector
        unordered_map<int, vecSzT> entryLocTbl;
        
        // Iterate over all vector element sequentially
        for (vecSzT i = 0; i != v.size(); ++i) {
            
            // Compute the pair entry which when added to current
            // vector element gives target sum 
            int pairEntry = target - v[i];
            
            // Check if this pair entry was already encountered in earlier
            // in teh vector
            if (entryLocTbl.find(pairEntry) != entryLocTbl.end()) {
                // Pair with given target sum found
                retV[0] = entryLocTbl[pairEntry];
                retV[1] = i;
                break;
            }
            
            // Target sum yet to be found, add current element and its
            // location to hash table
            entryLocTbl[v[i]] = i;
        }
                
        return retV;
    }
};
