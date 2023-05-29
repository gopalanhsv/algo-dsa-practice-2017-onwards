// n = grid egde size
// Time complexity per 'move' : O(1)
// Space complexity : O(n)
class TicTacToe {
public:
    TicTacToe(int n) {
        // Initialize the arrays/variables which track the sums and grid size
        _boardSz = n;
        _rowSumV.resize(n, 0);
        _colSumV.resize(n, 0);
        _forwardDiagSumV = 0;
        _reverseDiagSumV = 0;
    }
    
    int
    move(int row, int col, int player) {
        // Determine current player contribution to the sums
        // Player-1 contributes +1, while player-2 contributes -1
        int playerContrib = (player == 1) ? +1 : -1;
        // Add the player contribution to the respective row, col and diagonal(s)
        _rowSumV[row] += playerContrib;
        _colSumV[col] += playerContrib;
        if (row == col) {
            // Current move marks forward diagonal
            _forwardDiagSumV += playerContrib;
            if (_boardSz == _forwardDiagSumV || _boardSz + _forwardDiagSumV == 0) {
                // Foward diagonal fully occupied by current player
                return player;
            }
        }
        if (row + col == _boardSz - 1) {
            // Current move marks reverse diagonal
            _reverseDiagSumV += playerContrib;
            if (_boardSz == _reverseDiagSumV || _boardSz + _reverseDiagSumV == 0) {
                // Reverse diagonal fully occupied by current player
                return player;
            }
        }
        
        if ((_boardSz == _rowSumV[row]) || (_boardSz + _rowSumV[row] == 0)) {
            // Current row fully occupied by current player
            return player;
        }
        
        if ((_boardSz == _colSumV[col]) || (_boardSz + _colSumV[col] == 0)) {
            // Current column fully occupied by current player
            return player;
        }
        
        // Current move does not result in any winners
        return 0;
    }
    
private:
    
    // Data members
    // Track each move on a per player basis, adding +1 for player-1; -1 for player-2
    // to the appropriate row sum, column sum, and if required be the appropriate diagonal sums
    // If any diagonal, row or column gets fully populated by a particular player
    // then the respective diagonal sum/row sum/column sum will add upto to either
    // the +ve grid size (for player 1)/-ve grid size(for player 2) determining
    // the winner identity
    vector<int> _rowSumV;
    vector<int> _colSumV;
    int _forwardDiagSumV;
    int _reverseDiagSumV;
    int _boardSz;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
