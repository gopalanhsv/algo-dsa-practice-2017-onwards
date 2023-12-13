// n => nums1.size(), m => nums2.size()
// Time complexity : O(max(m, n))
// Space complexity : O(n + m)
class Solution {
public:
    vector<int>
    findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        // Build hash table of elements in both 'nums1', 'nums2'
        unordered_set<int> nums1Tbl(nums1.begin(), nums1.end());
        unordered_set<int> nums2Tbl(nums2.begin(), nums2.end());
        
        // Count of indices in 'nums1' whose elements are present in 'nums2'
        auto inNums2Cnt = 0;
        for (auto & num1 : nums1) {
            if (nums2Tbl.find(num1) != nums2Tbl.end()) {
                ++inNums2Cnt;
            }
        }
        // Count of indices in 'nums2' whose elements are present in 'nums1'
        auto inNums1Cnt = 0;
        for (auto & num2 : nums2) {
            if (nums1Tbl.find(num2) != nums1Tbl.end()) {
                ++inNums1Cnt;
            }
        }
        
        return {inNums2Cnt, inNums1Cnt};
    }
};
