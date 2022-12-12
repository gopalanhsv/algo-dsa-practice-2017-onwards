class Solution {
public:
    vector<vector<int>>
    threeSum(vector<int>& nums) {
        // Sort the numbers array in ascending order to easily
        // check and avoid duplicate triplets; and also to find
        // the three sum via two pointer method
        sort(nums.begin(), nums.end());
        
        // Search for a, b. and c at different indices 
        // s.t a + b + c = 0 OR b + c = -a
        // => Iterate through the array sequentially fixing the value of 'a';
        // and use two pointers on the subarray to the right of 'a' to search
        // for 'b' & 'c' s.t. b + c = -a 
        vector<vector<int> > tripletsV;
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            if ((0 != i) && (nums[i] == nums[i - 1])) {
                // To avoid duplicate triplets
                continue;
            }
            
            // Fixing the value 'a'
            auto a = nums[i];
            // Search for b, c in the closed range [i + 1, n - 1] s.t b + c = -a
            // Initially position the pointers at the end of range
            int lo = i + 1;
            int hi = n - 1;
            while (lo < hi) {
                // Compute b + c
                int twoSum = nums[lo] + nums[hi];
                if (twoSum == -a) {
                    // b + c equals required sum. Triplet found
                    vector<int> triplet({a, nums[lo], nums[hi]});
                    tripletsV.emplace_back(triplet);
                    // Skip duplicate 'b's
                    while ((lo < hi) && (nums[lo] == nums[lo + 1])) {
                        ++lo;
                    }
                    // Advance pointers to reset search range
                    ++lo;
                    --hi;
                } else if (twoSum < -a) {
                    // b + c is l.t required sum. Need to increase one of the values
                    // to get closer to require sum. Can only increase 'b'
                    ++lo;
                } else {
                    // b + c is g.t required sum. Need to decrease one of the values
                    // to get closer to require sum. Can only decrease 'c'
                    --hi;
                }
            }
        }
        
        return tripletsV;
    }
    
};
