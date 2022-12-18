class Solution {
public:
    vector<int>
    nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        // Every element in nums2 and nums1 is unique;
        // with nums1 elements being a subset of nums2
        
        // Hash table mapping each element in nums2 to its
        // next greater element
        unordered_map<int, int> elemToNextGreaterTbl;
        // Find the next greater element for each element in
        // 'nums2' using a monotonic stack; and populate the
        // above hash table
        // Stack of monotonically increasing elements in 'nums2'
        // (holds only the element indices and not the elements)
        // as seen on a L->R scan
        stack<int> monoStk;
        // Iterate over each element in 'nums2' from L->R
        for (int i = 0; i != nums2.size(); ++i) {
            auto & currElem = nums2[i];
            // Find all elements in 'nums2' to the left of current
            // element who have the current element as the next
            // greater element to the right
            while (!monoStk.empty() &&
                   (currElem > nums2[monoStk.top()])) {
                // Elements stored in stack are indices of elements
                // in 'nums2' to the left of current element
                
                // Current element is the next greater element of
                // the element to its left at index stored at stack top
                // Update hash table with this info
                elemToNextGreaterTbl[nums2[monoStk.top()]] = currElem;
                
                monoStk.pop();
            }
            // Add index of current element to monotonic stack
            monoStk.push(i);
        }
        
        // Elements remaining in the monotonic stack dont have
        // any next greater element
        while (!monoStk.empty()) {
            elemToNextGreaterTbl[nums2[monoStk.top()]] = -1;
            monoStk.pop();
        }
        
        // Iterate over each element in 'nums1'. Lookup the
        // element in hash table and find its next greater
        // element value from there
        vector<int> nextGreaterElemV(nums1.size());
        for (int i = 0; i != nums1.size(); ++i) {
            auto & num = nums1[i];
            nextGreaterElemV[i] = elemToNextGreaterTbl[num];
        }
        
        return nextGreaterElemV;
    }
};
