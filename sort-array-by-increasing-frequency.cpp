// n => nums.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)

class Solution {
public:
    vector<int>
    frequencySort(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums;
        }
        
        // Build frequency count table for the array
        unordered_map<int, int> freqCntTbl;
        for (auto n : nums) {
            freqCntTbl[n]++;
        }
        
        // Iterate over frequency table
        // Create a table grouping elements with same frequency.
        // The table entries are arranged in ascending order of their frequency, while
        // elements within a group of same frequency are arranged in descending order
        map<int, set<int, greater<int> >, less<int> > frequencyToElemSetTbl;
        for (auto & hte : freqCntTbl) {
            frequencyToElemSetTbl[hte.second].insert(hte.first);
        }
        
        // Create output vector. Iterate over the frequencies in ascending order
        vector<int> outV;
        for (auto & ent : frequencyToElemSetTbl) {
            int freq = ent.first;
            auto & elemsSet = ent.second;
            // Iterate over all elements of teh current frequency count
            for (auto e : elemsSet) {
                // freq copies of element added to output
                for (auto i = 0; i != freq; ++i) {
                    outV.emplace_back(e);
                }
            }
        }
        
        return outV;
    }
};
