// n => nums.size(), q => queries.size()

// AP Terms validation Approach
// Time complexity : O(qn)
// Space complexity : O(n)

// Sorting Approach
// Time complexity : O(qnlogn)
// Space complexity : O(n)

class Solution {
public:
    vector<bool>
    checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        
        return checkViaAPParamsValidation(nums, l, r);
        //return checkViaSorting(nums, l, r);
    }
    
private:
    
    bool
    validateIfSubarrayFormsAnAP(vector<int>& nums, int sIdx, int eIdx) {
            // last term = first term + (nterms * ap common diff)
        // Determine min and max term of subarray
        auto minVal = nums[sIdx];
        auto maxVal = nums[sIdx];
        for (auto i = sIdx + 1; i <= eIdx; ++i) {
            minVal = min(minVal, nums[i]);
            maxVal = max(maxVal, nums[i]);
        }
        
        if (minVal == maxVal) {
            // Subarray is an AP with identical terms
            return true;
        }
        
        // Min and max terms of subarray form the first and last terms of sequence respectively
        auto & ft = minVal;
        auto & lt = maxVal;
        // Subarray size/num terms
        auto nt = eIdx - sIdx + 1;
        // Compute the expected common difference between succesive sequence elements
        // is the subarray is to form an AP; i.e. range of vals [ft, lt] should be
        // divisible equally into (nt - 1) blocks; where each block has a size of
        // common diff
        if (0 != (lt - ft) % (nt - 1)) {
            // Not possible to divide val range into 'nt - 1' blocks of equal size
            // => subarray is not an AP
            return false;
        }
        auto cDiff = (lt - ft) / (nt - 1);

        vector<bool> apTermExistsForIdx(nt, false);
        for (int j = sIdx; j <= eIdx; ++j) {
            int currentTermDiffFromFirst = nums[j] - ft;
            int termIdx = currentTermDiffFromFirst / cDiff;
            if ((0 != currentTermDiffFromFirst % cDiff) || 
                termIdx >= nt ||
                apTermExistsForIdx[termIdx]) {
                // Subarray does not form an AP
                return false;
            }
            apTermExistsForIdx[termIdx] = true;
        }
        
        // Subarray forms an AP
        return true;
    }
    
    vector<bool>
    checkViaAPParamsValidation(vector<int>& nums, vector<int>& l, vector<int>& r) {

        // Validate the subarray specificed by each query as to to
        // whether it forms a valid AP (arithmetic progression) or not
        vector<bool> resultV;
        // Process each query
        for (int i = 0; i != l.size(); ++i) {
            auto sIdx = l[i];
            auto eIdx = r[i];
            auto subArrSz = eIdx - sIdx + 1;
            
            // Subarray is an AP if it has only one/two elements
            if (subArrSz <= 2) {
                resultV.emplace_back(true);
                continue;
            }
            
            // Check if the given subarray sequence is a valid AP with given
            // computed parameters
            resultV.push_back(validateIfSubarrayFormsAnAP(nums, sIdx, eIdx));
        }
        
        return resultV;
    }

    vector<bool>
    checkViaSorting(vector<int>& nums, vector<int>& l, vector<int>& r) {
        // Copy subarray specificed by a query to a a new array
        // Sort the new array and check if it is a valid AP
        // (arithmetic progression)

        vector<bool> resultV;
        // Process each query
        for (int i = 0; i != l.size(); ++i) {
            auto sIdx = l[i];
            auto eIdx = r[i];
            auto subArrSz = eIdx - sIdx + 1;
            
            // Subarray is an AP if it has only one/two elements
            if (subArrSz <= 2) {
                resultV.emplace_back(true);
                continue;
            }
            
            // Create a new array with the subarray elements
            vector<int> numsV(nums.begin() + sIdx, nums.begin() + sIdx + subArrSz);
            // Sort new array
            sort(numsV.begin(), numsV.end());
            // Determine the common difference betweeb first 2 elems of sorted sequence
            auto commonDiff = numsV[1] - numsV[0];
            // For the sorted sequence to be an AP, all adjacent elements should have
            // identical common diff
            bool isAP = true;
            for (auto j = 1; j < subArrSz; ++j) {
                if (numsV[j] - numsV[j - 1] != commonDiff) {
                    isAP = false;
                    break;
                }
            }
            resultV.emplace_back(isAP);
        }
        
        return resultV;
    }
    
};
