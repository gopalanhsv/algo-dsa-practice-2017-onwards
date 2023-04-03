// Time compexity : O(max(nums1.size() + nums2.size()))
// Space complexity : O(1)

class Solution {
public:
    int
    minNumber(vector<int>& nums1, vector<int>& nums2) {
        // Since both 'nums1' and 'nums2' consist of only single digit
        // numbers, the smallest number that contains at least one digit
        // from each would be one of the following :-
        // 1. Single digit number which is present in both
        //    'nums1' and 'nums2'; OR
        // 2. Two digit number which consist of the minimum digit in
        //    'nums1' and the minimum digit in 'nums2' (with the smallest
        //     of the selected digits in tens location and the other in
        //     the units location)

        int digitsInNums1 = 0;
        // Find min digit in 'nums1'
        int minDigitInNums1 = nums1[0];
        for (auto & d : nums1) {
            minDigitInNums1 = min(d, minDigitInNums1);
            digitsInNums1 |= (1 << d);
        }

        // Find min digit in 'nums1' and min common digit across both 'nums1' & 'nums2'
        int minDigitInBothNums1AndNums2 = 10;
        int minDigitInNums2 = nums2[0];
        for (auto & d : nums2) {
            minDigitInNums2 = min(d, minDigitInNums2);
            if (digitsInNums1 & (1 << d)) {
                // Current digit in both 'nums1' & 'nums2'
                // Update the min common digit across 'nums1' & 'nums2'
                minDigitInBothNums1AndNums2 = min(minDigitInBothNums1AndNums2, d);
            }
        }
        
        // Option 1
        if (10 != minDigitInBothNums1AndNums2) {
            return minDigitInBothNums1AndNums2;
        }
        
        // Option 2
        return 
            (min(minDigitInNums1, minDigitInNums2) * 10) + 
            (max(minDigitInNums1, minDigitInNums2));
    }
};
