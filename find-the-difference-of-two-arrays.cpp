// Bitset approach
// Time complexity : O(nums1.size()) + O(nums2.size())
// Space complexity : O(1)

// Hash table approach
// Time complexity : O(nums1.size()) + O(nums2.size())
// Space complexity : O(nums1.size()) + O(nums2.size())

class Solution {
public:
    vector<vector<int>>
    findDifference(vector<int>& nums1, vector<int>& nums2) {
        #ifdef STANDARD_HASH_TABLE_APPROACH
        unordered_set<int> nums1Elems;
        unordered_set<int> nums2Elems;
        for (auto & e : nums2) {
            nums2Elems.emplace(e);
        }

        vector<vector<int> > outV(2, vector<int>());
        auto & elemsInSet1AndNotInSet2V = outV[0];
        for (auto & e : nums1) {
            nums1Elems.emplace(e);
            if (nums2Elems.find(e) == nums2Elems.end()) {
                elemsInSet1AndNotInSet2V.emplace_back(e);
                nums2Elems.emplace(e);
            }
        }

        auto & elemsInSet2AndNotInSet1V = outV[1];
        for (auto & e : nums2) {
            if (nums1Elems.find(e) == nums1Elems.end()) {
                elemsInSet2AndNotInSet1V.emplace_back(e);
                nums1Elems.emplace(e);
            }
        }

        return outV;

        #else // OPTIMIZED BITSET APPROACH

        // Bitset used as hash table for tracking element presence
        // Since all elements are in range [-1000, 1000], normalize to
        // range [0, 2000]
        bitset<2001> nums1Elems;
        bitset<2001> nums2Elems;
        // Iterate over all elements in set#2
        for (auto & e : nums2) {
            // Mark element presence
            nums2Elems.set(e + 1000);
        }

        // Output/answer vector
        vector<vector<int> > outV(2, vector<int>());
        auto & elemsInSet1AndNotInSet2V = outV[0];

        // Iterate over all elements in set#1
        for (auto & e : nums1) {
            // Mark element presence
            nums1Elems.set(e + 1000);

            if (nums2Elems[e + 1000] == false) {
                // Current element in set#1 not in set#2, so added to output
                elemsInSet1AndNotInSet2V.emplace_back(e);
                // Ensure that duplicates are filtered out and not re-added to output
                nums2Elems.set(e + 1000);
            }
        }

        auto & elemsInSet2AndNotInSet1V = outV[1];
        // Iterate over all elements in set#2
        for (auto & e : nums2) {
            if (nums1Elems[e + 1000] == false) {
                // Current element in set#2 not in set#1, so added to output
                elemsInSet2AndNotInSet1V.emplace_back(e);
                // Ensure that duplicates are filtered out and not re-added to output
                nums1Elems.set(e + 1000);
            }
        }

        return outV;

        #endif
    }
};
