// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        int maxSum = 0;
        
        // Adopt the greedy approach of picking items marked '1', followed by
        // items marked '0' and then items marked '-1' in order to maximize
        // the sum of numbers written on the items being picked up
        
        // Pick items marked '1'
        if (k >= numOnes) {
            k -= numOnes;
            maxSum += numOnes;
        } else {
            return k;
        }

        // If any items left, pick items marked '0'
        if (k >= numZeros) {
            k -= numZeros;
        } else {
            return maxSum;
        }
        
        // If any items left, pick items marked '-1'
        maxSum -= k;
        
        return maxSum;
    }
};
