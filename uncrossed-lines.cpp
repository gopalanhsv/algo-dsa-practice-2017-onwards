// DP top down memoization approach
// Time complexity : O(nums1.size() x nums2.size())
// Space complexity : O(nums1.size() x nums2.size())

// DP bottom up tabulation
// Time complexity : O(nums1.size() x nums2.size())
// Space complexity : O(nums1.size() x nums2.size())

// DP bottom up tabulation optimized
// Time complexity : O(nums1.size() x nums2.size())
// Space complexity : O(nums2.size())

class Solution {
public:
    int
    maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        
        if (nums1.empty() || nums2.empty()) {
            // Base case of single/both array(s) being empty
            return 0;
        }
        
        //return maxLinesDpMemoization(nums1, nums2);
        //return maxLinesDpTabulation(nums1, nums2);
        return maxLinesDpTabulationOptimized(nums1, nums2);
    }
    
    
private:

    
    // Computes and caches the max number of connecting lines between
    // subarrays nums1[0, n1 - 1] and nums2[0, n2 - 1]
    int
    maxLinesDpMemoizationRec(
        vector<int>& nums1, int n1, vector<int>& nums2, int n2,
        vector<vector<int> >& memoTbl) {

        if (n1 <= 0 || n2 <= 0) {
            // Either/both of the substrings nums1[0, n1 - 1] or nums2[0, n2 - 1]
            // are empty => no uncrossed lines
            return 0;
        }
        
        if (-1 != memoTbl[n1][n2]) {
            // Max number of connecting lines between subarrays nums1[0, n1 - 1] and
            // nums2[0, n2 - 1] was computed and cached earlier. Return the
            // value from cache
            return memoTbl[n1][n2];
        }
        
        // Max number of connecting lines between subarrays nums1[0, n1 - 1]
        // and nums2[0, n2 - 1] will land in one of the following 3 cases:-
        // 1. Last char of subarray nums1[0, n1 - 1] excluded i.e. between
        // subarrays nums1[0, n1 - 2] and nums2[0, n2 - 1] 
        // 2. Last char of subarray nums2[0, n1 - 1] excluded i.e. between
        // subarrays nums1[0, n1 - 1] and nums2[0, n2 - 2] 
        // 3. Connecting line between last char of subarrays nums1[0, n1 - 1] &
        // nums2[0, n2 - 1] if they are identical, followed by the max connecting
        // lines between subarrays nums1[0, n1 - 2] and nums2[0, n2 - 2] 
        int maxLines =
            max(maxLinesDpMemoizationRec(nums1, n1 - 1, nums2, n2, memoTbl),
                maxLinesDpMemoizationRec(nums1, n1, nums2, n2 - 1, memoTbl));
        if (nums1[n1 - 1] == nums2[n2 - 1]) {
            maxLines =
                max(maxLines,
                    1 + maxLinesDpMemoizationRec(nums1, n1 - 1, nums2, n2 - 1, memoTbl));
        }
        
        // Update cache
        memoTbl[n1][n2] = maxLines;
        
        return maxLines;
    }
    
    int
    maxLinesDpMemoization(vector<int>& nums1, vector<int>& nums2) {
        int arr1Sz = nums1.size();
        int arr2Sz = nums2.size();
        // memoTbl[i][j] caches the max number of connecting lines between
        // subarrays nums1[0, i - 1] and nums2[0, j - 1] once it is computed
        // Initialed to "not yet computed" val of -1
        vector<vector<int> > memoTbl(arr1Sz + 1, vector<int>(arr2Sz + 1, -1));
        
        return maxLinesDpMemoizationRec(nums1, arr1Sz, nums2, arr2Sz, memoTbl);
    }
    
    int
    maxLinesDpTabulation(vector<int>& nums1, vector<int>& nums2) {
        int arr1Sz = nums1.size();
        int arr2Sz = nums2.size();
        // dpTbl[i][j] is the max number of connecting lines between
        // subarrays nums1[0, i - 1] and nums2[0, j - 1]
        vector<vector<int> > dpTbl(arr1Sz + 1, vector<int>(arr2Sz + 1, 0));
        
        // Iterate over all possible subarrays of nums1 which commence from left
        for (int i = 1; i <= arr1Sz; ++i) {
            // Iterate over all possible subarrays of nums2 which commence from left
            for (int j = 1; j <= arr2Sz; ++j) {
                
                // Compute the max number of connecting lines between
                // subarrays nums1[0, i - 1] and nums2[0, j - 1]

                // Max number of connecting lines between subarrays nums1[0, n1 - 1]
                // and nums2[0, n2 - 1] will land in one of the following 3 cases:-
                // 1. Last char of subarray nums1[0, n1 - 1] excluded i.e. between
                // subarrays nums1[0, n1 - 2] and nums2[0, n2 - 1] 
                // 2. Last char of subarray nums2[0, n1 - 1] excluded i.e. between
                // subarrays nums1[0, n1 - 1] and nums2[0, n2 - 2] 
                // 3. Connecting line between last char of subarrays nums1[0, n1 - 1] &
                // nums2[0, n2 - 1] if they are identical, followed by the max connecting
                // lines between subarrays nums1[0, n1 - 2] and nums2[0, n2 - 2] 
                int maxLines = max(dpTbl[i][j - 1], dpTbl[i - 1][j]);
                if (nums1[i - 1] == nums2[j - 1]) {
                    maxLines = max(maxLines, 1 + dpTbl[i - 1][j - 1]);
                }
                
                
                dpTbl[i][j] = maxLines;
            }
        }
        
        return dpTbl[arr1Sz][arr2Sz];
    }
    
    int
    maxLinesDpTabulationOptimized(vector<int>& nums1, vector<int>& nums2) {
        int arr1Sz = nums1.size();
        int arr2Sz = nums2.size();
        // dpTbl[i][j] is the max number of connecting lines between
        // subarrays nums1[0, i - 1] and nums2[0, j - 1]
        // Space optimized DP table is used with only 2 rows (as each computation
        // depends only on current and previous row values). Each 'i' is replaced
        // by 'i % 2' or 'i & 0x1'
        vector<vector<int> > dpTbl(2, vector<int>(arr2Sz + 1, 0));
        
        // Iterate over all possible subarrays of nums1 which commence from left
        for (int i = 1; i <= arr1Sz; ++i) {
            // Iterate over all possible subarrays of nums2 which commence from left
            for (int j = 1; j <= arr2Sz; ++j) {
                
                // Compute the max number of connecting lines between
                // subarrays nums1[0, i - 1] and nums2[0, j - 1]

                // Max number of connecting lines between subarrays nums1[0, n1 - 1]
                // and nums2[0, n2 - 1] will land in one of the following 3 cases:-
                // 1. Last char of subarray nums1[0, n1 - 1] excluded i.e. between
                // subarrays nums1[0, n1 - 2] and nums2[0, n2 - 1] 
                // 2. Last char of subarray nums2[0, n1 - 1] excluded i.e. between
                // subarrays nums1[0, n1 - 1] and nums2[0, n2 - 2] 
                // 3. Connecting line between last char of subarrays nums1[0, n1 - 1] &
                // nums2[0, n2 - 1] if they are identical, followed by the max connecting
                // lines between subarrays nums1[0, n1 - 2] and nums2[0, n2 - 2] 
                int maxLines =
                    max(dpTbl[(i & 0x1)][j - 1], dpTbl[((i - 1) & 0x1)][j]);
                if (nums1[i - 1] == nums2[j - 1]) {
                    maxLines = max(maxLines, 1 + dpTbl[((i - 1) & 0x1)][j - 1]);
                }
                
                dpTbl[(i & 0x1)][j] = maxLines;
            }
        }
        
        return dpTbl[(arr1Sz & 0x1)][arr2Sz];
    }
    
};
