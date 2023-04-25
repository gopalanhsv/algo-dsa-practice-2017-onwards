// Time complexity : O(seats.size())
// Space complexity : O(1)

class Solution {
public:
    int
    maxDistToClosest(vector<int>& seats) {

        // Adopting the greedy approach to maximize the distance to nearest person,
        // Alexs' seat must be placed either at the first seat or last seat (provided
        // they are empty) or at midpoint/median location between two people seated
        // sequentially. The option which gives max distance would be selected
        int nSeats = seats.size();

        // Move L->R skipping empty seats till first person with a seat is hit
        int seatLocation = 0;
        while (!seats[seatLocation]){
            ++seatLocation;
        }
        // First seat location with person while scanning from L->R
        int prevPersonSeatLocation = 0;
        int maxDistanceToClosestPerson = 0;
        if (seatLocation != 0) {
            // Attempt to place Alex at seat location 0
            maxDistanceToClosestPerson = seatLocation;
            prevPersonSeatLocation = seatLocation;
        }
        
        // Now attempt to place Alex at other possible optimal points
        for (++seatLocation; seatLocation != nSeats; ++seatLocation) {
            if (seats[seatLocation]) {
                // Current seat is filled
                // Attempt to place Alex at midpoint between
                // the previous filled position and current location
                int alexLocation = (prevPersonSeatLocation + seatLocation) / 2;
                maxDistanceToClosestPerson =
                    max(maxDistanceToClosestPerson,
                        min(seatLocation - alexLocation, alexLocation - prevPersonSeatLocation));
                
                // Advance to next filled seat location
                prevPersonSeatLocation = seatLocation;
            }
        }
        
        // Attempt to place Alex at last seat location if empty
        if (!seats[nSeats - 1]) {
            maxDistanceToClosestPerson =
                max(maxDistanceToClosestPerson, nSeats - 1 - prevPersonSeatLocation);
        }

        return maxDistanceToClosestPerson;
    }
};
