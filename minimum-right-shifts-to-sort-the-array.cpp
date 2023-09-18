// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    minimumRightShifts(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz <= 1) {
            // Base case of empty/single element array
            return 0;
        }

        // Since the array should have been initially sorted and rotated for right
        // shifts to make it sorted; the elements should be s.t each element is g.t
        // its preceeding element on moving from left to right except for at most
        // single index where the element would be l.t its predecessor (this would
        // be the sole element which will be at index 0 post the right shifts - minimum
        // valued element) 
        
        auto smallestElemCandidateIdx = -1;
        // Iterate over the array elements sequentially from L->R
        for (auto i = 1; i != arrSz; ++i) {
            if (nums[i] < nums[i - 1]) {
                if (smallestElemCandidateIdx != -1) {
                    // There cannot be 2 min valued elements for a sorted array
                    // => the array cannot be made sorted via rotation/shifting
                    return -1;
                }
                smallestElemCandidateIdx = i;
            }
        }
        
        if (-1 == smallestElemCandidateIdx) {
            // Array is already sorted => no shifts reqd
            return 0;
        }
        
        // The array has to be right shifted/rotated for making it sorted
        
        if (nums[arrSz - 1] > nums[0]) {
            // Right shifting wont lead to a sorted array as there are 2 points
            // where an element is lesser than its preceeding element
            return -1;
        }
        
        return arrSz - smallestElemCandidateIdx;
    }
};
