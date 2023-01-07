class Solution {
public:
    int
    canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    
        // Since the gas tank capacity is infinite, for the car to
        // be able to complete a full circuit, sum of fuel at all stops
        // should at least exceed the amount of fuel consumed between
        // the stops.
        // To find the starting gas station which allows a complete
        // circuit to be done successfully :-
        // Assume that our car is such that it can run with a 0 or deficit in
        // the tank (i.e. -ve gas).
        // Start at gas station 0 will no fuel and come back to it by making a
        // complete circuit of stations 0 -> 1 -> 2...-> n - 2 -> n - 1 -> 0;
        // At each gas station, fill tank with the entire gas station stock;
        // and between adjacent stations consume fuel from tank as per cost.T
        // Track the amount of fuel in tank on reaching the station prior to
        // filling up. The gas station at which the amount of fuel is the least
        // should be chosen as start point (it may be a -ve number). Setting
        // this point as the start point ensures having zero amount of fuel in
        // tank just prior to filling and commencing on trip; and at subsequent
        // fuel stops it is ensured thatthe car on just reaching there will have
        // no fuel deficit  -- a necessary condition to prevent car running out
        // of fuel on the way
        
        // Start at station 0 with no fuel
        int currStation = 0;
        int fuelInTank = gas[currStation];
        int minFuelInTank = gas[currStation];
        int gasStationWithMinFuel = currStation;
        int numStations = gas.size();
        
        int prevStation = 0;
        currStation = (currStation + 1) % numStations;

        do {
            // Fuel in tank just prior to reaching station 'currStation'
            fuelInTank -= cost[prevStation];
            // Check if amount of fuel in tank prior to filling up has
            // the least quantity amongst all stations
            if (fuelInTank < minFuelInTank) {
                gasStationWithMinFuel = currStation;
                minFuelInTank = fuelInTank;
            }
            
            if (0 == currStation) {
                // Reached back to station 0. Circuit loop done
                break;
            }
            
            // Fill tank with entire gas station stock
            fuelInTank += gas[currStation];
            
            // Advance to next station
            prevStation = currStation;
            currStation = (currStation + 1) % numStations;
            
        } while (true);
        
        if (fuelInTank < 0) {
            // Fuel is in deficit at end of round trip => entire fuel
            // available in all gas stations along route is insufficient
            // for a circular trip
            return -1;
        }
        
        return gasStationWithMinFuel;
    }
};
