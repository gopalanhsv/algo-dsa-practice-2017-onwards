// Time complexity : O(moves.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    furthestDistanceFromOrigin(string moves) {
        // Since the wildcards provide the option of either a 'R' or 'L' move while
        // the 'R' & 'L' impose a strict left/right movement, count the net movement
        // after the imposition of strict 'R' & 'L'; and use the wildcards to move in
        // the same direction of the net movement inorder to maximize the distance
        // from the origin
        auto nWildCards = 0;
        auto netRightDistDueToStrictMoves = 0;
        for (auto & move : moves) {
            if ('L' == move) {
                --netRightDistDueToStrictMoves;
            } else if ('R' == move) {
                ++netRightDistDueToStrictMoves;
            } else { // wildcard
                ++nWildCards;
            }
        }
        
        // Since we are interested only in distance from origin, use magnitude of net strict movement
        return abs(netRightDistDueToStrictMoves) + nWildCards;
    }
};
