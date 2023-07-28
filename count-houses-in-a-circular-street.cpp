// Time complexity : O(k)
// Space complexity : O(1)

/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void openDoor();
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 *     void moveLeft();
 * };
 */
class Solution {
public:
    int
    houseCount(Street* street, int k) {
        // Since the street is circular & has at most 'k' houses, visit 'k' houses
        // sequentially by moving in a single direction - closing each visited house door
        // Results in closing the doors of all houses situated on street
        for (int i = 0; i != k; ++i) {
            street->closeDoor();
            street->moveLeft();
        }
        
        // Now open the house door of the house in front of which person is standing
        // and move to the right
        int houseCnt = 1;
        street->openDoor();
        street->moveRight();
        // Go around the circular street moving to the right one house at a time, tracking the 
        // number of closed doors seen till the initial house (whose door was opened) is hit
        // The number of houses/closed doors seen can be used to determine the number of houses
        while (!street->isDoorOpen()) {
            street->moveRight();
            ++houseCnt;
        }
        
        return houseCnt;
    }
};
