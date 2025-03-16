// p => nums1.size(),q => nums2.size()
// Time Complexity : O(max(p, q)
// Space Complexity : O(1) {excluding the space required for result array}
class Solution {
public:
    vector<vector<int>>
    mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        // Since both the array contents are arranged in ascending order, use
        // merge algo of merge sort algorithm to merge the array contents
        int arr1Sz = nums1.size();
        int arr2Sz = nums2.size();
        
        // Ouput merged and sorted array
        vector<vector<int> > mergedArrV;
        // Pointers to next element with smallest identifier to processed
        // and written to output for both arrays
        int arr1Idx = 0;
        int arr2Idx = 0;
        while ((arr1Idx < arr1Sz) && (arr2Idx < arr2Sz)) {
            // Till both arrays are not fully explored
            
            auto & nums1Elem = nums1[arr1Idx];
            auto & nums2Elem = nums2[arr2Idx];
            auto & nums1Id = nums1Elem[0];
            auto & nums2Id = nums2Elem[0];
            
            if (nums1Id == nums2Id) {
                // array#1 and array#1 elements have same identifier
                // Output element should have same identifier and
                // value as sum of repective element values
                auto & nums1Val = nums1Elem[1];
                auto & nums2Val = nums2Elem[1];
                mergedArrV.push_back({nums1Id, nums1Val + nums2Val});
                // Advance both array pointers
                ++arr1Idx;
                ++arr2Idx;
            } else if (nums1Id < nums2Id) {
                // array#1 identifier is smaller
                // Output element should have same identifier and
                // value as that of array#1
                mergedArrV.emplace_back(nums1Elem);
                // Advance array#1 pointer
                ++arr1Idx;
            } else {
                // array#2 identifier is smaller
                // Output element should have same identifier and
                // value as that of array#2
                mergedArrV.emplace_back(nums2Elem);
                // Advance array#2 pointer
                ++arr2Idx;
            }
        }
        
        // Either of remaining portion of array#1/#2 elements may not
        // be fully explored. Explore and add to output
        while (arr1Idx < arr1Sz) {
            // Array#1 not fully explored. Explore and add to output
            auto & nums1Elem = nums1[arr1Idx];
            mergedArrV.emplace_back(nums1Elem);
            ++arr1Idx;
        }
        
        while (arr2Idx < arr2Sz) {
            // Array#2 not fully explored. Explore and add to output
            auto & nums2Elem = nums2[arr2Idx];
            mergedArrV.emplace_back(nums2Elem);
            ++arr2Idx;
        }
        
        return mergedArrV;
    }
};
