// n = nums.size()
// Binary search approach
// Time complexity : O(nlogn)
// Space complexity : O(1)

// Bitset approach
// Time complexity : O(n)
// Space complexity : O(1)

// Brute force approach
// Time complexity : O(n ^ 2)
// Space complexity : O(1)

// Floyd Algorithm/Hare and Tortoise approach
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    findDuplicate(vector<int>& nums) {
        return duplicateUsingFloydAlgorithm(nums);
        return duplicateUsingBinarySearch(nums);
    }
    
private:

    int
    duplicateUsingBinarySearch(vector<int>& nums) {
        int lowestPossibleDuplicate = 1;
        int highestPossibleDuplicate = nums.size() - 1;
        
        int l = lowestPossibleDuplicate;
        int r = highestPossibleDuplicate;
        while (l < r) {
            int mid = l + (r - l) / 2 ;
            if (noDuplicatesTillMid(nums, mid)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        
        return l;
    }
    
    bool
    noDuplicatesTillMid(vector<int>& nums, int mid) {
        int expectedCountTillMid = mid;
        int actualCntTillMid = 0;
        for (auto & x : nums) {
            if (x <= mid) {
                ++actualCntTillMid;
            }
        }
        
        return actualCntTillMid == expectedCountTillMid;
    }
    
    int
    duplicateUsingBitset(vector<int>& nums) {
        int n = nums.size();
        bitset<100001> seenNumsSet;
        for (auto & x : nums) {
            if (seenNumsSet[x]) {
                return x;
            }
            seenNumsSet.set(x);
        }
        return -1;
    }
    
    int
    duplicateUsingBruteForce(vector<int>& nums) {
        int arrSz = nums.size();
        for (auto i = 1; i != arrSz; ++i) {
            for (auto j = i - 1; j >= 0; --j) {
                if (nums[i] == nums[j]) {
                    return nums[i];
                }
            }
        }
        
        return -1;
    }
    
    int
    duplicateUsingFloydAlgorithm(vector<int>& nums) {
        
        int n = nums.size() - 1;
        // Since all numbers are in the range [1, n] and array indices are in the range [0, n],
        // the array can be modelled as a linked list of nodes wherein the array elements are
        // the nodes, and the next node/index for a node at index 'i' would be nums[i]. This
        // is due to the fact that there is difference of 1 between candidate least num in array
        // and least array index
        
        // As the array size is 'n + 1' and contains only 'n' unique values in the range [1, n],
        // by the pigeonhole principle there would be at least 2 duplicates present in the array.
        // Since there are at least 2 repeats (say the repeated element is 'r') present in the array,
        // the linked list nodes modelling these elements would have their next node/index as 
        // the same number 'r' -- in effect multiple elements cycling back to the same element.
        
        // So the problem reduces to having a cycle in a linked list and determining cycle start
        // point. This is done via Floyds' hare and tortoise algorithm i.e. employing a slow and fast
        // pointer with fast running at 2x the speed of slow
        
        // Determine the convergence point of the 2 pointers
        // by moving fast pointer at 2 steps at a time while the slow pointer moves one step
        int slowP = 0;
        int fastP = 0;
        do {
            slowP = nums[slowP];
            fastP = nums[nums[fastP]];
        } while (slowP != fastP);
        
        // Find the start/convergence point of cycle
        // Move slow pointer back to start point while the fast pointer stays put
        // Both of them move at the same speed now till they converge. Convergence
        // pont will be the repeated value 
        slowP = 0;
        while (slowP != fastP) {
            slowP = nums[slowP];
            fastP = nums[fastP];
        }
        
        return slowP;
    }
    
};
