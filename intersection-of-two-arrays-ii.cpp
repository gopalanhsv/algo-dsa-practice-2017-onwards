// m => v1.size(), n => v2.size()

// Hash table Approach
// Time complexity : O(m + n)
// Space complexity : O(max(m, n))

// Merge Sort Approach
// Time complexity : O(mlogm + nlogn)
// Space complexity : O(max(logm, logn))

class Solution {
public:
    vector<int>
    intersect(vector<int>& v1, vector<int>& v2) {
        //return intersectionViaSortMerge(v1, v2);
        
        if (v1.size() > v2.size()) {
            return intersectionViaHashTable(v1, v2);
        } else {
            return intersectionViaHashTable(v2, v1);            
        }
    }
    
private:
    
    vector<int>
    intersectionViaSortMerge(vector<int>& v1, vector<int>& v2) {
        // Sort the 2 arrays and then use merge technique from merge
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        
        auto i = 0, j = 0;
        vector<int> intersectV;
        while (i != v1.size() && j != v2.size()) {
            if (v1[i] < v2[j]) {
                ++i;
            } else if (v1[i] > v2[j]) {
                ++j;
            } else {
                // Entries in both vector are equal, add to intersection set
                intersectV.emplace_back(v1[i]);
                ++i, ++j;
            }
        }
        
        return intersectV;
    }
    
    vector<int>
    intersectionViaHashTable(vector<int>& vb, vector<int>& vs) {
        
        unordered_map<int, int> bigSetHashTbl;
        for (auto & e : vb) {
            bigSetHashTbl[e]++;
        }
        
        vector<int> intersectV;
        // Iterate over the smaller set of elements. Search for occurrences of
        // them in bigger set for intersection
        for (auto & e: vs) {
            auto tblIter = bigSetHashTbl.find(e);
            if ((tblIter != bigSetHashTbl.end()) && (tblIter->second != 0)) {
                intersectV.emplace_back(e);
                tblIter->second--;
            }
        }
        
        return intersectV;
    }
};
