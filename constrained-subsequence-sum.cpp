// n => nums.size()

// Monotonic Q Approach
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    constrainedSubsetSum(vector<int>& nums, int k) {
        return subSeqSumViaMonotonicQApproach(nums, k);
    }
    
private:
    
    int
    subSeqSumViaMonotonicQApproach(vector<int>& nums, int k) {
        auto arrSz = nums.size();
        
        // dpTbl[i] is the max constrained subsequence sum for the
        // subsequence which terminates at and includes element at 
        // index 'i' i.e. nums[i]
        vector<int> dpTbl(arrSz, 0);

        // (A) Subsequence which terminates at an index 'j' can have its 2nd last element
        // element (if any) at the furthest point 'i' s.t. j - i <= k
        // That is, the preceeding element (if any) for a subsequence terminating at an
        // index 'j' must be within a window of size 'k' => requirement of a sliding window
        // of size 'k' which ends at index 'j' 
        // (B) For a subsequence S[j] terminating at an index 'j' to have the max sum:-
        // 1. If the max sum subsequences terminating at the candidate preceeding elements
        // (within a window size 'k') are all -ve, S[j] will consist only of sole element
        // nums[j]
        // 2. If some of the max sum subsequences terminating at the candidate preceeding
        // elements (within a window size 'k') are + ve, S[j] will consist of last element
        // being nums[j] and max valued preceeding subsequence S[i] within the window of
        // size 'k' wherein j - i <= k
        
        // The above 2 requirements call for all candidate preceeding subsequence sum S[i]
        // values preceeding element nums[j] to be maintained in a window s.t max element
        // and leaving candidates (those not satisfying the window length 'k' condition) to be
        // easily accessible. 
        // One can either use a max heap consisting of {S[x], x} pairs or use a 
        // monotonic Q with valid indices 'i' arranged in descending order of S[i] values
        
        // Going for a monotonic Q implementation here
        // windowQ consisting of valid candidate preceeding subsequence element indices 'i' 
        // arranged in descending order of S[i] values from Q front to back at every
        // index being examined
        deque<int> windowQ;
        // Iterate sequentially over the subsequence terminating elements from L-> R 
        // (these will form the end of the window)
        for (auto winEnd = 0; winEnd < arrSz; ++winEnd) {
            
            // Max sum subsequence S[winEnd] terminates at nums[winEnd]
            auto lastElem = nums[winEnd];
            
            // Dump all indices 'i' which cannot be valid preceeding elements
            // for S[winEnd] i.e. outside window range of size 'k'
            while (!windowQ.empty() && ((winEnd - windowQ.front()) > k)) {
                windowQ.pop_front();
            }

            // S[winEnd] consists of nums[winEnd] and the max sum subsequence
            // within the valid window of size 'k' (index of the same will be
            // at front of Q as indices 'i' are arranged withing the Q in descending
            // order of dpTbl[i] values)
            dpTbl[winEnd] = lastElem;                                        
            if (!windowQ.empty()) {
                dpTbl[winEnd] += dpTbl[windowQ.front()];
            }
            
            // Discard all indices 'x' from Q/window which terminate subsequences
            // with max values l.t. max sum subsequence at current index 'winEnd'
            // as current index becomes a better preceeding candidate for following 
            // subsequences
            while (!windowQ.empty() && dpTbl[winEnd] > dpTbl[windowQ.back()]) {
                windowQ.pop_back();
            }
            
            // Add current index to end of Q (skip indices terminating -ve valued
            // max sum subsequences as these will just bring down the overall sum
            // if telescoped with any subsequence indices)
            if (dpTbl[winEnd] > 0) {
                windowQ.push_back(winEnd);
            }
        }
        
        return *max_element(dpTbl.begin(), dpTbl.end());
    }
};
