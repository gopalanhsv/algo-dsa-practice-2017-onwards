class Solution {
public:
    void
    solve(vector<vector<char>>& board) {
        
        // This is a variant of the boundary flood fill problem
        // Iterate over all the boundary cells. On encountering
        // and 'O' cell, commence a BFS/DFS (4 directional) from
        // to visit all the reachable 'O' cells. Mark all these
        // 'O' cells reachable from the boundary as 'T'
        _nr = board.size();
        _nc = board[0].size();
        
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };
        
        // Flood fill DFS/BFS from cells marked 'O' on left
        // and right boundary of board
        for (int r = 0; r != _nr; ++r) {
            if (board[r][0] == 'O') {
                //floodFillDFS(r, 0, board);
                floodFillBFS(r, 0, board);
            }
            if (board[r][_nc - 1] == 'O') {
                //floodFillDFS(r, _nc - 1, board);
                floodFillBFS(r, _nc - 1, board);
            }
        }
        // Flood fill DFS/BFS from cells marked 'O' on top
        // bottom right boundary of board
        for (int c = 0; c != _nc; ++c) {
            if (board[0][c] == 'O') {
                //floodFillDFS(0, c, board);
                floodFillBFS(0, c, board);
            }
            if (board[_nr - 1][c] == 'O') {
                //floodFillDFS(_nr - 1, c, board);
                floodFillBFS(_nr - 1, c, board);
            }
        }
        
        // Now iterate over the entire board. 'O' Cells which were reachable
        // from boundary 'O' in earler board are marked 'T' and cannot be captured.
        // Change them to 'O'. Cells which stay 'O' can be captured (isolated
        // islands), mark them as 'X'
        for (int r = 0; r != _nr; ++r) {
            for (int c = 0; c != _nc; ++c) {
                if (board[r][c] == 'T') {
                    board[r][c] = 'O';
                } else if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                } 
            }
        }
    }
    
private:
    
    void
    floodFillDFS(int r, int c, vector<vector<char>>& board) {
        
        // Add start cell to DFS stack and mark it as visited
        _dfsStk.push(pair<int, int>(r, c));
        board[r][c] = 'T';

        // Commence DFS
        while (!_dfsStk.empty()) {
            // Pop off the cell at top of DFS stack
            auto & v = _dfsStk.top();
            int X = v.first;
            int Y = v.second;
            _dfsStk.pop();
            
            // Explore the neighbours of popped off cell and
            // set up the reachable 'O' cells for a DFS visited

            for (auto & noffs : _nbrOffsetsV) {
                // Neighbor coords
                int nX = X + noffs.first;
                int nY = Y + noffs.second;
                
                // Only valid 'O' neighours are setup for visit
                if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc && board[nX][nY] == 'O') {
                    // Add neigbour to DFS stack and mark it as visited
                    _dfsStk.push(pair<int, int>(nX, nY));
                    board[nX][nY] = 'T';
                }
            }
        }
    }

    void
    floodFillBFS(int r, int c, vector<vector<char>>& board) {
        
        typedef queue<pair<int, int> >::size_type qSzT;
        
        // Add start cell to BFS Q and mark it as visited
        _bfsQ.push(pair<int, int>(r, c));
        board[r][c] = 'T';

        // Commence BFS
        while (!_bfsQ.empty()) {
            qSzT currLvlSz = _bfsQ.size();
            // Visit all cells queued up in the BFS Q and explore their neighbours
            for (qSzT i = 0; i != currLvlSz; ++i) {
            
                // Dequeue the cell at Q front
                auto & v = _bfsQ.front();
                int X = v.first;
                int Y = v.second;
                _bfsQ.pop();
            
                // Explore the neighbours of dequeued off cell and
                // enqueue up the reachable 'O' cells for a BFS visit

                for (auto & noffs : _nbrOffsetsV) {
                    // Neighbor coords
                    int nX = X + noffs.first;
                    int nY = Y + noffs.second;
                
                    // Only valid 'O' neighours are setup for visit
                    if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc && board[nX][nY] == 'O') {
                        // Enqueue neigbour to BFS Q and mark it as visited
                        _bfsQ.push(pair<int, int>(nX, nY));
                        board[nX][nY] = 'T';
                    }
                }
            }
        }
    }
    
    // Data members
    // Num rows, cols
    int _nr;
    int _nc;
    // 4 directional neighbour offsets vector
    vector<pair<int, int> > _nbrOffsetsV;
    // DFS stack
    stack<pair<int, int> > _dfsStk;
    // BFS queue
    queue<pair<int, int> > _bfsQ;
};
