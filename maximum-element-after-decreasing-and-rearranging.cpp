// n => arr.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)
class Solution {
public:
    int
    maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        // Since the array elements can be only decreased or sorted (and not increased),
        // the maximum valued element post processing would be that element which is
        // decreased by the least amount (such that the array elements satisfy the
        // specified constraints)
        // First element must be 1 and difference betn adjacent element must be l.e 1,
        // Sort the array elements in ascending order as this enables elements with
        // min diff between them to be placed in adjacent locations and subsequently
        // quick processing of array (decreasing values) from L->R s.t array meets
        // the specified conditions
        sort(arr.begin(), arr.end());
        // Process the array from L->R sequentially s.t first element is 1 and
        // adjacent element diff is l.e 1. 
        auto nElems = arr.size();
        auto prevElem = 1; // first element of array
        for (auto i = 1; i < nElems; ++i) {
            // Current element pre-processing
            auto elem = arr[i];
            // New value of current element post-processing (either 1 more than previous
            // adjacent element due to ascending formation or same as old value/no change
            // i.e identical adjacent values)
            auto newElemVal = min(elem, prevElem + 1);
            
            prevElem = newElemVal;
        }
        // Max valued element would be the rightmost array element post processing
        return prevElem;
    }
};
