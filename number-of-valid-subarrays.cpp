class Solution {
public:
    
    int
    validSubarrays(vector<int>& nums) {
        // Leftmost element of the valid subarray should always be the
        // minimum element of the subarray
        // An element nums[i] in 'nums' forms valid subarrays till each of the indices
        // j wherein j >= i & nums[i] = min(nums[i], nums[i + 1], ...., nums[j])
        // => An element nums[i] in 'nums' forms valid subarrays from index 'i' till each
        // of the indices prior to j wherein j > i, nums[j] < nums[i]
        // => An element nums[i] in 'nums' forms valid subarrays from index 'i' till each
        // of the indices prior to next smaller element to its right at j wherein j > i
        
        // The valid subarrays formed from an element nums[i] till the index 'j - 1' prior
        // to the next smaller element at index 'j' would be of the ranges
        // [i, i], [i, i + 1], [i, i + 2], ....., [i, j - 1]
        // => Number of valid subarrays having nums[i] as the leftmost/minimum element
        // would be j - 1 - i + 1 = j - i valid subarrays where nums[j] is the next smaller
        // element to the right for nums[i] with j > i
        
        // Since the next smaller/greater element can be quickly and efficiently determined
        // using a monotonic stack, the same approach is employed here
        
        // Stack of element indices whose next smaller element to the right is not yet determined
        stack<int> monoStk;
        auto nTotalValidSubArrays = 0;
        for (auto i = 0; i != nums.size(); ++i) {
            // Current element at 'i'
            auto & curr = nums[i];
            
            // Determine all the indices to the left of/prior to current index 'i'
            // which have 'curr' as the next smaller element
            while (!monoStk.empty()) {
                auto prevElemIdx = monoStk.top();
                if (curr >= nums[prevElemIdx]) {
                    break;
                }
                monoStk.pop();
                
                // nums[prevElemIdx] has nums[i]/curr as next smaller element
                // => nums[prevElemIdx] would be the leftmost element for the valid subarrays
                //[prevElemIdx, prevElemIdx], [prevElemIdx, prevElemIdx + 1], [prevElemIdx, prevElemIdx + 1]
                // ......., [prevElemIdx, i - 1] i.e i - prevElemIdx valid subarrays
                nTotalValidSubArrays += i - prevElemIdx;
            }
            
            monoStk.push(i);
        }
        
        // For the remaining element indices in the stack, the next smaller element would be
        // -infinity located just beyond the last element i.e. valid subarrays will extend from
        // element indices in stack (forming the leftmost element) to the right end of the array
        while (!monoStk.empty()) {
            auto prevElemIdx = monoStk.top();
            monoStk.pop();
                
            // nums[prevElemIdx] has -infinity as next smaller element
            // => nums[prevElemIdx] would be the leftmost element for the valid subarrays
            //[prevElemIdx, prevElemIdx], [prevElemIdx, prevElemIdx + 1], [prevElemIdx, prevElemIdx + 1]
            // ......., [prevElemIdx, nums.size() - 1] i.e i - prevElemIdx valid subarrays
            nTotalValidSubArrays += nums.size() - prevElemIdx;
        }
        
        return nTotalValidSubArrays;
    }
};
