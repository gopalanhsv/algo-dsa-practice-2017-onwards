// n1 = nums1.size(), n2 => nums2.size()

// Constructor : 
// Time complexity : O(max(n1, n2))
// Space complexity : O(n1 + n2)

// add()
// Time complexity : O(1)

// count()
// Time complexity : O(n1)

class FindSumPairs {
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) : _nums2V(nums2) {
        // Build frequency count table of elements in nums1 & nums2
        for (auto & e : nums1) {
            _nums1FreqCntTbl[e]++;
        }
        for (auto & e : nums2) {
            _nums2FreqCntTbl[e]++;
        }
    }
    
    void
    add(int index, int val) {
        if (index >= _nums2V.size()) {
            // 'index' out of array bounds => delta not applied
            return;
        }
        
        // Old value of nums2 at index is changed 
        // => decrement occurence count of old value
        auto & nums2Val = _nums2V[index];
        if (--_nums2FreqCntTbl[nums2Val] == 0) {
            _nums2FreqCntTbl.erase(nums2Val);
        }
        // update the value in nums2 at given index and its occurence count
        nums2Val += val;
        _nums2FreqCntTbl[nums2Val]++;
    }
    
    int
    count(int tot) {
        
        int nPairs = 0;
        // Iterate over each distint value of nums1
        for (auto & nums1TblEntry : _nums1FreqCntTbl) {
            auto & nums1Val = nums1TblEntry.first;
            
            // Compute required complementary nums2 value for current
            // nums1Val s.t their sum is 'tot'
            auto reqdNums2Val = tot - nums1Val;
            // Lookup presence of complementary nums2 value 
            auto it = _nums2FreqCntTbl.find(reqdNums2Val);
            if (it != _nums2FreqCntTbl.end()) {
                // Complementary value is found in 'nums2'
                auto & nums1ValFreqCnt = nums1TblEntry.second;
                auto & nums2ValFreqCnt = it->second;
                
                // Number of pairs formed by current nums1 value and its complementary
                // would be the product of the respective occurence counts
                nPairs += (nums1ValFreqCnt * nums2ValFreqCnt);
            }
        }
        
        return nPairs;
    }
    
private:

    // Data members
    // Tables tracking occurence count of elems in nums1 & nums2
    unordered_map<int, int> _nums1FreqCntTbl;
    unordered_map<int, int> _nums2FreqCntTbl;
    // Deep copy of nums2 (used for applying value modifications)
    vector<int> _nums2V;
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
