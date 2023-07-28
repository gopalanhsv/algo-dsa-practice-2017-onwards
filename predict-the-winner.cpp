// n => nums.size()

// DP memoization (top down)
// Time complexity : O(n x n)
// Space complexity : O(n x n)

// DP iterative (bottom up)
// Time complexity : O(n x n)
// Space complexity : O(n x n)

class Solution {
public:
    bool
    PredictTheWinner(vector<int>& nums) {
        if (nums.size() == 1) {
            // Base case of single element array, player#1 will always win
            return true;
        }
        
        // For player#1 to win the game,
        // total player#1 score >= total player#2 score
        // => total player#1 score - total player#2 score >= 0
        // => score diff >= 0
        // Player#1 will do his best to maximize the score diff for winning the game
        // Player#2 will do his best to minimize the score diff for winning the game
        // Explore all possible play options by both player#1 and 2 via DP to
        // track the net score differenece
        
        //return winnerViaTopDownMemoization(nums);
        return winnerViaDPIterative(nums);
    }
    
private:
    
    int
    maxScoreViaTopDownMemoizationRec(vector<int>& nums, int lo, int hi, int playerId) {
        // Player 'playerId' is player in order to win the game using
        // subarray range [lo, hi]
        
        if (lo == hi) {
            // single element array
            // Player#1 score adds to score diff (to maximize)
            // Player#2 score subtracts from score diff (to minimize)
            return (0 == playerId) ? nums[lo] : -nums[lo];
        }
        
        if (_scoreDiffTbl[playerId][lo][hi] != numeric_limits<int>::min()) {
            // Required score was cached in earlier iterations
            return _scoreDiffTbl[playerId][lo][hi];
        }
        
        // Compute the score diff when player 'playerId' attempts
        // to win the game with subarray [lo, hi]
        int scoreDiff = 0;
        if (0 == playerId) {
            // Player#1 tries to maximize the score diff. Can choose either nums[lo] or
            // nums[hi] and handover the remainder of subarray to player#2 for next turn
            scoreDiff = 
                max(nums[lo] + maxScoreViaTopDownMemoizationRec(nums, lo + 1, hi, 1),
                    nums[hi] + maxScoreViaTopDownMemoizationRec(nums, lo, hi - 1, 1));
        } else {
            // Player#2 tries to minimize the score diff. Can choose either nums[lo] or
            // nums[hi] and handover the remainder of subarray to player#1 for next turn
            scoreDiff = 
                min(-nums[lo] + maxScoreViaTopDownMemoizationRec(nums, lo + 1, hi, 0),
                    -nums[hi] + maxScoreViaTopDownMemoizationRec(nums, lo, hi - 1, 0));
        }
        
        // Update the cache with compute score diff
        _scoreDiffTbl[playerId][lo][hi] = scoreDiff;
        return scoreDiff;
    }
    
    bool
    winnerViaTopDownMemoization(vector<int>& nums) {
        // Initialize the score difference cache table
        int arrSz = nums.size();
        _scoreDiffTbl.resize(
            2, 
            vector<vector<int> >(arrSz, vector<int>(arrSz, numeric_limits<int>::min())));
        
        // Determine net score diff for player#1 over entire array range
        // via memoization consideraing all cases recursively
        maxScoreViaTopDownMemoizationRec(nums, 0, arrSz - 1, 0);
        // For player#1 to win, score diff should be g.e. 0 over entire
        // array range for player#1
        return _scoreDiffTbl[0][0][arrSz - 1] >= 0;
    }
    
    bool
    winnerViaDPIterative(vector<int>& nums) {
        // Initialize the score difference cache table
        int arrSz = nums.size();
        _scoreDiffTbl.resize(2, 
            vector<vector<int> >(arrSz, vector<int>(arrSz, numeric_limits<int>::min())));

        for (int i = 0; i != arrSz; ++i) {
            // Single element array
            // Player#1 score adds to score diff (to maximize)
            // Player#2 score subtracts from score diff (to minimize)
            _scoreDiffTbl[0][i][i] = nums[i];
            _scoreDiffTbl[1][i][i] = -nums[i];
        }
        
        // Iterate over all possible subarray sizes sequentially
        for (int subArrSz = 2; subArrSz <= arrSz; ++subArrSz) {
            // Iterate over all possible subarrays of given size
            int maxLo = arrSz - subArrSz;
            for (int lo = 0; lo <= maxLo; ++lo) {
                // Subarray of size 'subArrSz' extends over the range [lo, hi]
                int hi = lo + subArrSz - 1;
                // Compute the score diff for each player using the current subarray
                
                // Player#1 tries to maximize the score diff. Can choose either nums[lo] or
                // nums[hi] and handover the remainder of subarray to player#2 for next turn
                _scoreDiffTbl[0][lo][hi] = max(
                    nums[lo] + _scoreDiffTbl[1][lo + 1][hi], 
                    nums[hi] + _scoreDiffTbl[1][lo][hi - 1]);
                // Player#2 tries to minimize the score diff. Can choose either nums[lo] or
                // nums[hi] and handover the remainder of subarray to player#1 for next turn
                _scoreDiffTbl[1][lo][hi] = min(
                    -nums[lo] + _scoreDiffTbl[0][lo + 1][hi], 
                    -nums[hi] + _scoreDiffTbl[0][lo][hi - 1]);
            }
        }

        // For player#1 to win, score diff should be g.e. 0 over entire
        // array range for player#1
        return _scoreDiffTbl[0][0][arrSz - 1] >= 0;
    }
    
    // Data members
    // Score difference cache table for player#1 score - player#2 scoe 
    // _scoreDiffTbl[p][l][r] is the score difference when player 'p' plays
    // the game optimally using the subarray nums[l, r] in order to win
    // Player#1 => p is 0, Player#2 => p is 1
    vector<vector<vector<int> > > _scoreDiffTbl;
};
