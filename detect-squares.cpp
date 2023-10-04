// Time complexity : 
// add() : O(1)
// count() : O(n) , 'n' is number of points added so far

// Space complexity :
// O(n) , 'n' is number of points added so far
class DetectSquares {
public:
    DetectSquares() {
    }
    
    void
    add(vector<int> point) {
        // Add point to hash table
        auto & x = point[0];
        auto & y = point[1];
        _xyCoordFreqCntTbl[x][y]++;
    }
    
    int
    count(vector<int> point) {
        int totalSquaresCnt = 0;
        // Query point
        auto & px = point[0];
        auto & py = point[1];
        int queryPointCnt = 1;
        // Iterate over all the points which have the same 'x' co-ord as 'px'
        // i.e. the points of the vertical line parallel to Y-axis passing thru (px, py)
        auto & verticalLinePointsTbl = _xyCoordFreqCntTbl[px];
        for (auto & vlpInfo : verticalLinePointsTbl) {
            auto & ny = vlpInfo.first;
            auto p1Cnt = vlpInfo.second;
            if (p1Cnt == 0) {
                continue;
            }
            // Vertical distance between the points (this would be square side length)
            auto d = ny - py;
            if (d != 0) {
                // Candidate square vertical side endpoints are Q(px, py) & P1(px, ny)
                // Two square formations are possible (i.e 2 horizontal sides and the remaining
                // vertical side) :-
                // (1) With points P2(px - d, py) & P3(px - d, ny) to left of candidate vertical side
                // (2) With points P2(px + d, py) & P3(px + d, ny) to rigt of candidate vertical side
                
                // Occurrence count of each of these points for scenario (1)
                auto p2Cnt = _xyCoordFreqCntTbl[px - d][py];
                auto p3Cnt = _xyCoordFreqCntTbl[px - d][ny];
                // Number of squares possible with Q, P1, P2, P3
                totalSquaresCnt += (queryPointCnt * p1Cnt * p2Cnt * p3Cnt);
                // Occurrence count of each of these points for scenario (2)
                p2Cnt = _xyCoordFreqCntTbl[px + d][py];
                p3Cnt = _xyCoordFreqCntTbl[px + d][ny];
                // Number of squares possible with Q, P1, P2, P3
                totalSquaresCnt += (queryPointCnt * p1Cnt * p2Cnt * p3Cnt);
            }
        }
        
        return totalSquaresCnt;
    }
    
private:
    
    // Data members
    // Hash table of all point co-ords mapped to occurrence count of points
    unordered_map<int, unordered_map<int, int> > _xyCoordFreqCntTbl;
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
