// n = nums1.size() = nums2.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    vector<int>
    anagramMappings(vector<int>& nums1, vector<int>& nums2) {
        vector<int> outV;
        // Base case of empty input vector(s)
        if (nums1.empty() || nums2.empty()) {
            return outV;
        }
        
        // Build a hash table mapping nums2 elements to their
        // respective indices
        unordered_map<int, vector<int> > elemToPosTbl;
        int pos = 0;
        for (auto & e : nums2) {
            elemToPosTbl[e].emplace_back(pos++);
        }
        
        outV.resize(nums1.size());
        // Iterate over num1 elements sequentially, get their
        // locations in nums2 via hash table
        pos = 0;
        for (auto & e : nums1) {
            outV[pos++] = elemToPosTbl[e].back();
            elemToPosTbl[e].pop_back();
        }
        
        return outV;
    }
};
