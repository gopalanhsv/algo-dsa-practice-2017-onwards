// n => arr.size()
// Time complexity : O(min(k, n))
// Space complexity : O(1)

class Solution {
public:
    int
    getWinner(vector<int>& arr, int k) {
        // If 'k' is g.t.e to the array length, the winner would be the maximum
        // element in the array as it would repeatedly get selected once hit
        
        // If 'k' is l.t the array length, simulate the game till by making a
        // single pass through the array till an integer is found with 'k' wins
        
        auto arrSz = arr.size();
        auto nWins = 0;
        auto maxElem = arr[0];
        // Tracks the winning element retained from the previous win
        // Initialized to the first winning element
        auto prevWinElem = max(arr[0], arr[1]);
        // Iterate over over the array sequentially from L->R
        for (auto i = 1; i < arrSz; ++i) {
            // Current iteration win
            auto currWinElem = max(prevWinElem, arr[i]);
            if (currWinElem == prevWinElem) {
                // Current iteration win element is identical to previous
                // Update win count
                if (++nWins == k) {
                    // 'k' successive wins with the same element
                    return currWinElem;
                }
            } else {
                // Current iteration win element is a new one.
                // Update the winning element and reset win count
                nWins = 1;
                prevWinElem = currWinElem;
            }
            // Maximum element
            maxElem = max(maxElem, arr[i]);
        }
        
        // Maximum array element wins as all array element have been examined once
        return maxElem;
    }
};
