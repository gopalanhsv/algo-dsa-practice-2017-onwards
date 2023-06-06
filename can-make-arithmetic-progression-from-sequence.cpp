// arr.size() => n
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    bool
    canMakeArithmeticProgression(vector<int>& arr) {
        // Sort array elements in ascending order s.t
        // that all elements appear in sequential order
        sort(arr.begin(), arr.end());
        
        // If sequence is an AP, common diff between
        // each consecutive element would be same
        typedef vector<int>::size_type vecSzT;
        // Common diff between first 2 elements of sequence
        int apCommonDiff = arr[1] - arr[0];
        // Iterate over sequence determining the diff between consecutive elements
        for (vecSzT i = 2; i != arr.size(); ++i) {
            if (arr[i] - arr[i - 1] != apCommonDiff) {
                // Sequence is not an AP due to failure in common diff criteria
                return false;
            }
        }
        
        return true;        
    }
};
