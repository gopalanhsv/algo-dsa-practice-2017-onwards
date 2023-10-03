// n => start/end.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    canTransform(string start, string end) {
        if (start.size() != end.size()) {
            // Length mismatch => transformation fails
            return false;
        }
        
        auto strSz = start.size();
        // Following two observations can be made from the allowed transitions:
        // 1. 'XL' can be replaced by 'LX' => 'L' can be moved to the left to take any of the
        // locations of 'X' if there is a series of 'X' immediately prior to 'L'; till halted
        // by another 'L'/'R'
        // 2. 'RX' can be replaced by 'XR' => 'R' can be moved to the right to take any of the
        // locations of 'X' if there is a series of 'X' immediately following 'R'; till halted
        // by another 'L'/'R'

        // From above:-
        // 1) 'L' can move only to left
        // 2) 'R' can move only to right
        // 3) 'L' & 'R' cannot cross each other
        // 4) 'X' can be treated as empty spaces except for length comparison
        
        // Use 2 pointers pointing to 'start' & 'end' string and advance them checking
        // that the char transformations exhibit the consistency laid out above 
        int pStart = 0;
        int pEnd = 0;
        while ((pStart < strSz) || (pEnd < strSz)) {
            
            // Skip 'X' till 'L'/'R'/start string end is reached
            while ((pStart < strSz) && (start[pStart] == 'X')) {
                ++pStart;
            }
            // Skip 'X' till 'L'/'R'/end string end is reached
            while ((pEnd < strSz) && (end[pEnd] == 'X')) {
                ++pEnd;
            }
            
            if ((pStart == strSz) || (pEnd == strSz)) {
                // End of least one of either 'start'/'end' string end is hit
                // => Exit loop as at least one string wont have chaars to compare
                break;
            }
            
            // 'L'/'R' char hit in both the 'start' & 'end' string
            // Exec consistency check
            
            if (start[pStart] == 'L')  {
                // 'L' char hit in 'start' => 'L' should also be hit in 'end'
                // as L/R crossover not allowed. Since 'L' can move only to left
                // 'L' in 'end' should be either to left/same position as in 'start'
                if ((end[pEnd] != 'L') || (pEnd > pStart)) {
                    // Crossover have occurred in 'start' & 'end' OR
                    // 'L' in 'start' is to the right of corresponding 'L' in 'end'
                    return false;
                }
            } else {
                // start[pStart] == 'R'
                // 'R' char hit in 'start' => 'R' should also be hit in 'end'
                // as L/R crossover not allowed. Since 'R' can move only to right
                // 'R' in 'end' should be either to right/same position as in 'start'
                if ((end[pEnd] != 'R') || (pEnd < pStart)) {
                    // Crossover have occurred in 'start' & 'end' OR
                    // 'R' in 'start' is to the left of corresponding 'R' in 'end'
                    return false;
                }
            }
            
            // Advance pointers for both strings to resume checks
            ++pStart;
            ++pEnd;
        }
        
        // Both start and end should have been fully seen/parsed;
        // else some mismatch chars remain at end of start/target
        return ((pStart == strSz) && (pEnd == strSz));
    }
};
