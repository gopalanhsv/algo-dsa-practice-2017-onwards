// n => start.size()/target.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    canChange(string start, string target) {
        if (start == target) {
            // Identical strings => no change
            return true;
        }

        if (start.size() != target.size()) {
            // String of unequal size => transformation fails
            return false;
        }
        
        // Relative ordering of 'R' and 'L' is preserved as per 'start' string
        // post movement of L/R to the empty spaces leading to 'end'. Empty spaces are occupied
        // only by an unblocked 'L' to the right; or by an unblocked 'R' to the left
        
        // Following two observations can be made from the allowed transitions:
        // 1. 'L' can be moved to the left to take any of the locations of '_' if there is a
        // series of '_' immediately prior to 'L'; till halted by another 'L'/'R'
        // 2. 'R' can be moved to the right to take any of the locations of '_' if there is a
        // series of '_' immediately following 'R'; till halted by another 'L'/'R'

        // From above:-
        // 1) 'L' can move only to left
        // 2) 'R' can move only to right
        // 3) 'L' & 'R' cannot cross each other
        // 4) Empty spaces are of use for length comparison
        
        // Use 2 pointers pointing to 'start' & 'target' string and advance them checking
        // that the char transformations exhibit the consistency laid out above 

        int strSz = start.size();
        int sIdx = 0;
        int tIdx = 0;
        while ((sIdx < strSz) || (tIdx < strSz)) {
            // Skip spaces in 'target' till L/R/end of string hit
            while ((tIdx < strSz) && (target[tIdx] == '_')) {
                ++tIdx;
            }
            
            // Skip spaces in 'start' till L/R/end of string hit
            while ((sIdx < strSz) && (start[sIdx] == '_')) {
                ++sIdx;
            }
            
            if ((sIdx == strSz) || (tIdx == strSz)) {
                // End of least one of either 'start'/'target' string end is hit
                // => Exit loop as at least one string wont have chars to compare
                break;
            }
            
            // L/R char hit in both 'start' and 'target'. Exec consistency check
            if (target[tIdx] == 'L') {
                // 'L' char hit in 'target' => 'L' should also be hit in 'start'
                // as L/R crossover not allowed. Since 'L' can move only to the left,
                // 'L' in 'target' should be either to left/same position as in 'start'
                if ((start[sIdx] != 'L') || (sIdx < tIdx)) {
                    // Crossover have occurred in 'start' & 'target' OR
                    // 'L' in 'target' is to the right of corresponding 'L' in 'start'
                    return false;
                }
            } else {
                // target[tIdx] == 'R'
                // 'R' char hit in 'target' => 'R' should also be hit in 'start'
                // as L/R crossover not allowed. Since 'R' can move only to the right,
                // 'R' in 'target' should be either to right/same position as in 'start'
                if ((start[sIdx] != 'R') || (sIdx > tIdx)) {
                    // Crossover have occurred in 'start' & 'target' OR
                    // 'R' in 'target' is to the left of corresponding 'R' in 'start'
                    return false;
                }
            }
            
            // Advance pointers in start and target
            ++sIdx, ++tIdx;
        }

        // Both start and target should have been fully seen/parsed;
        // else some mismatch chars remain at end of start/target
        return (sIdx >= strSz) && (tIdx >= strSz);
    }
};
