// n1 = nums1.size(), n2 => nums2.size()
// Time complexity : O(max(n1, n2))
// Space complexity : O(1)

class Solution {
public:
    long long
    minSum(vector<int>& nums1, vector<int>& nums2) {
        // Compute num zeros and sum of non-zero elems in nums1
        auto sum1 = 0LL;
        auto nZeros1 = 0LL;
        for (auto & num1 : nums1) {
            sum1 += num1;
            if (0 == num1) {
                ++nZeros1;
            }
        }
        // Compute num zeros and sum of non-zero elems in nums2
        auto sum2 = 0LL;
        auto nZeros2 = 0LL;
        for (auto & num2 : nums2) {
            sum2 += num2;
            if (0 == num2) {
                ++nZeros2;
            }
        }
        
        // Compute min possible sum of nums1 & nums2 by making all zeros +ve
        // i.e. make all zeros as 1 for min possible sum
        long long minSumNum1 = sum1 + nZeros1;
        long long minSumNum2 = sum2 + nZeros2;

        if (nZeros1 && nZeros2) {
            // Both arrays have zeros, min equal sum possible would be the max value 
            // of the min possible sums of either array; as the array having smaller
            // of the sum can have its some one (obtained from a zero) to be replaced 
            // by larger number to make the array sums equal
            return max(minSumNum1, minSumNum2);
        }

        if (!nZeros1 && !nZeros2) {
            // Both arrays have nil zeros => no replacement of nums possible in either
            // No way to get equal sum until already pre-existing
            return (minSumNum1 == minSumNum2) ? minSumNum1 : -1; 
        }
        
        // One of the arrays has nil zeros (no sum change possible for particular array);
        // Other array has zeros => this array sum can be increasing by replacing zeros
        // by +ve integers; and it can be increased at most equal to that of other array
        // (with no zeroes)
        if (!nZeros1) {
            // nums1 has no zeros => min equal sum can be array sum of nums1
            // provided nums2 min possible sum is same or lower
            return (minSumNum2 <= minSumNum1) ? minSumNum1 : -1;
        }
        
        // nums2 has no zeros => min equal sum can be array sum of nums2
        // provided nums1 min possible sum is same or lower
        return (minSumNum1 <= minSumNum2) ? minSumNum2 : -1;
    }
};
