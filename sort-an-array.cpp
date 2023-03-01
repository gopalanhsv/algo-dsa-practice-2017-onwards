class Solution {
public:
    vector<int>
    sortArray(vector<int>& nums) {
        //return mergeSort(nums);
        return countingSort(nums);
    }
    
private:
    
    vector<int>
    mergeSort(vector<int>& numV) {
        mergeSort(numV, 0, numV.size() - 1);
        return numV;
    }
    
    void
    mergeSort(vector<int>& subArrV, int lo, int hi) {
        if (lo >= hi) {
            return;
        }
        
        // Partition the current subarray [lo, hi]
        // into two halves
        int mid = lo + (hi - lo) / 2;
        // Sort the two halves of the subarray recursively
        mergeSort(subArrV, lo, mid);
        mergeSort(subArrV, mid + 1, hi);

        // Merge the two sorted halves of the current subarray
        // s.t that complete subarray gets sorted via out of
        // place merge
        vector<int> sortedV(hi - lo + 1);
        int sortedIdx = 0;
        int loIdx = lo;
        int hiIdx = mid + 1;
        while ((loIdx <= mid) && (hiIdx <= hi)) {
            if (subArrV[loIdx] <= subArrV[hiIdx]) {
                sortedV[sortedIdx++] = subArrV[loIdx++];
            } else {
                sortedV[sortedIdx++] = subArrV[hiIdx++];
            }
        }
        while (loIdx <= mid) {
            sortedV[sortedIdx++] = subArrV[loIdx++];
        }
        while (hiIdx <= hi) {
            sortedV[sortedIdx++] = subArrV[hiIdx++];
        }
        
        // Copy the sorted array contents back to the original subarray
        for (int i = lo; i <= hi; ++i) {
            subArrV[i] = sortedV[i - lo];
        }
    }
    
    vector<int>
    countingSort(vector<int>& numV) {
        
        // Determine array max and min
        int minVal = numV[0];
        int maxVal = numV[0];
        for (auto & elem : numV) {
            minVal = min(minVal, elem);
            maxVal = max(maxVal, elem);
        }
        // Array element range
        int elemRangeSz = maxVal - minVal + 1;
        // Contruct frequency count table for each of the
        // array elements with each array element normalized
        // (all elems are normalized in the same manner with
        // min array element normalized down to 0)
        vector<int> countV(elemRangeSz, 0);
        for (auto & elem : numV) {
            auto elemKey = elem - minVal;
            countV[elemKey] += 1;
        }

        // Sort the array using the frequency count table
        // of normalized elements
        int arrIdx = 0;
        // Iterate over each normalized elem value in ascending order
        for (int normalizedElem = 0; normalizedElem != elemRangeSz; ++normalizedElem) {
            // Original element value for the current normalized element is
            // placed in the sorted array as per the frequency count
            while (countV[normalizedElem] > 0) {
                --countV[normalizedElem];
                numV[arrIdx++] = minVal + normalizedElem;
            }
        }
        
        return numV;
    }
};
