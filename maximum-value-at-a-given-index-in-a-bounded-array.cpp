// Time complexity : O(log maxSum) / O(log n)
// Space complexity : O(1)

class Solution {
public:
    int
    maxValue(int n, int index, int maxSum) {
        // Constraint on array elements to be +ve integers and all elements
        // sum l.e 'maxSum' => an array element can have the max possible value
        // of 'maxSum' and min possible value of '1'

        // Since element at specified index 'index' needs to be maximized, adopt
        // the greedy approach of always location the maximum element in the array
        // at the specified index; and then gradually decrement the elements to
        // placed on either side of the 'index' by '1' at each step (in order to 
        // meet the constraint placed on adjacent element values) till the number
        // '1' is hit/array bounds reached. Afterwards have the element as '1'
        // till the array bounds are hit as array elements have to be +ve.
        // Rapid decrement of element values on either side of the max valued
        // element is done in order to ensure that the sum of all array elements
        // is least possible value (s.t constraint on 'maxSum' is met)
        
        // Experiment with the above approach for various possible values of
        // element at 'index' via binary search; and determine the max value
        // possible leading to an array satisfying all constraints
        int loMaxVal = 1;
        int hiMaxVal = maxSum;
        
        while (loMaxVal < hiMaxVal) {
            int midMaxVal = loMaxVal + (hiMaxVal - loMaxVal) / 2 + 1;
            if (arrayPossibleWithGivenMaxVal(midMaxVal, index, n, maxSum)) {
                loMaxVal = midMaxVal;
            } else {
                hiMaxVal = midMaxVal - 1;
            }
        }
        
        
        return loMaxVal;
    }
    
private:
    
    bool
    arrayPossibleWithGivenMaxVal(int maxVal, int maxValIdx, int arrSz, int maxSum) {
        // Determine all elements sum for array with min possible sum with given 
        // constraints and having a maximum element value of 'maxVal' at 'maxvalIdx'
        
        // Compute sum of elements to left of max element at 'maxValIdx'
        // i.e. range [0, maxValIdx - 1]
        long nLeftElems = maxValIdx;
        long maxElemToLeftOfMaxValIdx = maxVal - 1;
        long minElemToLeftOfMaxValIdx = max(1L, maxElemToLeftOfMaxValIdx + 1 - nLeftElems);
        long nElemsFormingAP = maxElemToLeftOfMaxValIdx - minElemToLeftOfMaxValIdx + 1;
        long leftElemsSum =
            nElemsFormingAP * (minElemToLeftOfMaxValIdx + maxElemToLeftOfMaxValIdx) / 2;
        if (nLeftElems > nElemsFormingAP) {
            long nAllOnesElems = nLeftElems - nElemsFormingAP;
            leftElemsSum += nAllOnesElems;
        }
        
        // Compute sum of elements to right of max element at 'maxValIdx'
        // i.e. range [maxValIdx + 1, arrSz - 1]
        long nRightElems = arrSz - (maxValIdx + 1);
        long maxElemToRightOfMaxValIdx = maxVal - 1;
        long minElemToRightOfMaxValIdx = max(1L, maxElemToLeftOfMaxValIdx + 1 - nRightElems);
        nElemsFormingAP = maxElemToRightOfMaxValIdx - minElemToRightOfMaxValIdx + 1;
        long rightElemsSum =
            nElemsFormingAP * (minElemToRightOfMaxValIdx + maxElemToRightOfMaxValIdx) / 2;
        if (nRightElems > nElemsFormingAP) {
            long nAllOnesElems = nRightElems - nElemsFormingAP;
            rightElemsSum += nAllOnesElems;
        }
        
        long allElemsSum = maxVal + leftElemsSum + rightElemsSum;
        
        return allElemsSum <= maxSum;
    }
};
