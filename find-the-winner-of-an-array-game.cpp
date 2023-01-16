class Solution {
public:
    int
    getWinner(vector<int>& arr, int k) {
        // If 'k' is g.t.e to the array length, the winner would be the maximum
        // element in the array as it would repeatedly get selected once hit
        
        // If 'k' is l.t the array length, simulate the game till by making a
        // single pass through the array till an integer is found with 'k' wins
        
        int arrSz = arr.size();
        int nWins = 0;
        int maxElem = arr[0];
        // Tracks the winning element which is retained from the
        // previous win. Initialized to the first winning element
        int prevWinElem = max(arr[0], arr[1]);
        // Iterate over each element of the array sequentially
        for (int i = 1; i < arrSz; ++i) {
            // Element which wins in the current iteration
            int currWinElem = max(prevWinElem, arr[i]);
            if (currWinElem == prevWinElem) {
                // Element winning current iteration is same as that
                // in the previous iteration. Increment number of
                // consequent wins
                ++nWins;
                if (nWins == k) {
                    // 'k' consequent wins with the same element
                    return currWinElem;
                }
            } else {
                // Element winning current iteration is not same as that
                // in the previous iteration. Reset the number of win and
                // the winning element
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
