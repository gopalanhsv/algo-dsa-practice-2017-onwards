// Time complexity : O(nuts.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {
        // Since squirrel can carry at most one nut at a time, it has to go to nut location, then deposit
        // nut in tree prior to hunting for the next(if any) nut. There is no way for the squirrel to
        // reduce the number of moves by doing a shortest path tour of all nuts collecting them and finally
        // caching all in one shot in the tree.
        
        // Min number of moves between any two locations is the respective manhattan/taxi distance
        // as the squirrel can move only in 4 direction bteween adjacent cells
        
        // The only optimization possible is the choice of first move by squirrel
        // (1) Squirrel moves from start to one of the nut locations, collects it and deposits to tree; and then
        //     from tree to all of the other nut locations, collection and back to tree for deposit
        // (2) Squirrel moves from start to tree locations;  and then from tree to all the nut locations,
        //     collection and back to tree for deposit
        

        // Compute total min moves done by squirrel commencing from tree to collect all nuts
        int nCollectionMovesFromTree = 0;
        auto & treePos = tree;
        for (auto & nutPos : nuts) {
            // Number of moves required between tree and current nut
            int nMoves = abs(nutPos[0] - tree[0]) + abs(nutPos[1] - tree[1]);
            // Twice the above required to go from tree to nut, collect and back
            nCollectionMovesFromTree += 2 * nMoves;
        }
        
        // Have the tree as first hop and collection moves from tree to each nut and back 
        // Min moves to travel from start to tree
        int nFirstHopMoves = abs(squirrel[0] - tree[0]) + abs(squirrel[1] - tree[1]);
        // Total min moves required when first hop is from start location to tree
        int totalMoves = nFirstHopMoves + nCollectionMovesFromTree;
        
        // Have one of the nut locations as first hop move, first collection from selected first nut/hop
        // location to tree; and all other collection moves from tree to other nut locations and back
        for (auto & nutPos : nuts) {
            // Current nut at 'nutPos' is selected as first hop
            // Min moves reqd to travel from start to first hop
            nFirstHopMoves = abs(nutPos[0] - squirrel[0]) + abs(nutPos[1] - squirrel[1]);
            // Min moves reqd to deposit collected nut from 'nutPos' to tree
            int nSecondHopMoves = abs(nutPos[0] - tree[0]) + abs(nutPos[1] - tree[1]);
            // Min moves reqd to collect all the other nuts and deposit in tree
            int nRemainingCollectionMoves = nCollectionMovesFromTree - (2 * nSecondHopMoves);
            
            // Update the min moves seen so far
            totalMoves = min(totalMoves, nFirstHopMoves + nSecondHopMoves + nRemainingCollectionMoves);
        }
        
        return totalMoves;
    }
};
