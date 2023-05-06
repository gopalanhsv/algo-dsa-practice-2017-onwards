// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    int
    minMoves(vector<int>& nums) {
        if (nums.size() < 2) {
            return 0;
        }
        
        // In a move, incrementing n - 1 elements and keeping remaining single
        // element identical, is equivalent to decrementing the sole single element.
        // Problem reduces to finding the minimum number of moves via a single
        // element decrement operation per move to make all elements equal.

        // Since it makes no sense to decrement minimum val in the array,
        // the minimum moves method to achieve this goal is to make all elements
        // equal to the minimum value.
        
        // Total number of moves is just sum of differences of all elements
        // from the minimum element = sum of elements - array size * min elem
        
        long sum = nums[0]; // Using long to avoid overflows
        int minElem = nums[0];
        int nSize = nums.size();
        for (int i = 1; i != nSize; ++i) {
            sum += nums[i];
            minElem = min(minElem, nums[i]); 
        }
        
        return int(sum - long(nSize * minElem));
    }
};
