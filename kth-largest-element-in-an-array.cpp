// n => nums.size()

// Heap Approach
// Time complexity : O(nlogk)
// Space compelxity : O(k)

// Partition/QuickSelect Approach
// Time complexity : O(n)
// Space compelxity : O(1)
class Solution {
public:
    int
    findKthLargest(vector<int>& nums, int k) {
        
        if (nums.size() < k) {
            // Array size doesn't accomodate 'k' elements
            // So invalid input
            return -1;
        }

        //return kthLargestViaHeap(nums, k);
        return kthLargestViaQuickSelect(nums, nums.size() - k);
    }
    
private:
    
    int
    partition(vector<int>& nums, int l, int r, int pivotIdx) {
        int pivotElem = nums[pivotIdx];
        swap(nums[pivotIdx], nums[r]);
        int wrIdx = l;
        for (int i = l; i < r; ++i) {
            if (nums[i] < pivotElem) {
                swap(nums[wrIdx++], nums[i]);
            }
        }
        swap(nums[wrIdx], nums[r]);
        return wrIdx;
    }
    
    int
    kthLargestViaQuickSelect(vector<int>& nums, int k) {
    
        default_random_engine randGen;
        
        int l = 0;
        int r = nums.size() - 1;
        while (true) {
        
            // Randomly select a pivot index/element in the
            // range [l, r]/[nums[l], nums[r]]
            uniform_int_distribution<int> d(l, r);
            int pivotIdx = d(randGen);
            pivotIdx = partition(nums, l, r, pivotIdx);
            
            if (pivotIdx == k) {
                return nums[pivotIdx];
            } else if (pivotIdx > k) {
                r = pivotIdx - 1;
            } else {
                l = pivotIdx + 1;
                //k -= pivotIdx;
            }
        }
        
        return -1;
    }
    
    int
    kthLargestViaHeap(vector<int>& nums, int k) {
        
        // Iterate over the elements in the vector sequentially. Maintain a
        // collection of the largest 'k' elements seen so far using a min heap
        priority_queue<int, vector<int>, greater<int> > minHeap;
        int nElems = nums.size();
        // Iterate over vector elements sequentially
        for (auto & e : nums) {
            // Add element to heap. If heap collection size exceeds 'k',
            // dump the minimum element. This ensures that heap contains
            // collection of 'k' largest elements seen so far
            minHeap.push(e);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // At the end, heap will have collection of 'k' largest elements in
        // vector; with largest element at heap bottom and 'k' largest element
        // at heap top
        return minHeap.top();
    }
};
