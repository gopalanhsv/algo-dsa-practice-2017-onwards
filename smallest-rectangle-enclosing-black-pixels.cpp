// Time complexity : O(num black pixels)
// Space complexity : O(num black pixels)

class Solution {
public:
    int
    minArea(vector<vector<char>>& image, int x, int y) {
        // Commence a BFS/DFS from the given black pixel cell location(x, y)
        // Restrict BFS/DFS traversal to only the black pixels. Track the min & max
        // values of the X & Y coords seen during the BFS/DFS traversal
        // Since all black pixels are connected and there is only a single black
        // region; the min & max values of the X & Y coords seen during the BFS/DFS
        // traversal can be used to determine the smallest rectangle boundary coords
        // enclosing the black region OR the length + breadth of the aforesaid rectangle
        
        // Num rows/cols of the matrix
        int nr = image.size();
        int nc = image[0].size();
        // 4 directional movement direction offsets to a neighbor cell
        vector<pair<int, int> > nbrOffsetsV = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
        };
        
        // Tracks the min/max X/Y co-ords of black reqion explored so far
        int minX = numeric_limits<int>::max();
        int minY = numeric_limits<int>::max();
        int maxX = numeric_limits<int>::min();
        int maxY = numeric_limits<int>::min();
        
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        // The image grid matrix itself is used as a 'cell visited' marker for
        // a black pixel/cell by marking it to 'white'/'0'
        // Commence BFS from the given black pixel
        bfsQ.push({x, y});
        image[x][y] = '0'; // Marking (x, y) as visited
        while (!bfsQ.empty()) {
            int currLvlSz = bfsQ.size();
            // Visit all the cells/black pixels at the current level
            for (int i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the pixel at front of BFS Q
                auto & cellCoords = bfsQ.front();
                int X = cellCoords.first;
                int Y = cellCoords.second;
                bfsQ.pop();
                // Update the min & max value of X & Y black pixel coords
                // seen so far
                minX = min(minX, X);
                maxX = max(maxX, X);
                minY = min(minY, Y);
                maxY = max(maxY, Y);
                // Schedule any unvisited 4-directional adjacent black cell
                // (neighbour) for a BFS visit in the subsequent iteration
                for (auto & nbrOffset : nbrOffsetsV) {
                    // Neighbour coords
                    int nX = X + nbrOffset.first;
                    int nY = Y + nbrOffset.second;
                    
                    if ((nX >= 0) && (nY >= 0) && (nX < nr) && (nY < nc) &&
                        (image[nX][nY] == '1')) {
                        // Valid unvisited 4-directional adjacent black cell
                        // scheduled for a BFS visit                        
                        bfsQ.push({nX, nY});
                        image[nX][nY] = '0';
                    }
                }
            }
        }
                 
        // Dimensions of smallest rectangle enclosing the black pixel region
        auto rectXLen = maxX - minX + 1;
        auto rectYLen = maxY - minY + 1;
        // Area of smallest rectangle
        return rectXLen * rectYLen;
    }
};
